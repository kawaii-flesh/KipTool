import sys
import configparser
import re
import json

def find_element_by_regex(data_array, regex_pattern):
    for item in data_array:
        match = re.search(regex_pattern, item)
        if match:
            return item
    return None

nameReg = r"\[\*(.*)\]"
def parse_ini(data_array, wizardSourcePath):
    obj = {}    
    platformReg = r"; (Mariko|Erista)"
    jsonmarkcurkipReg = r"json_mark_cur_kip '\/switch\/\.packages\/4IFIR Wizard\/(.*\.json)' name (\d+)"
    jsonmarkcurkip = find_element_by_regex(data_array, jsonmarkcurkipReg)
    if(jsonmarkcurkip != None):
        jsonmarkcurkipFounded = re.search(jsonmarkcurkipReg, jsonmarkcurkip)
        obj['name'] = re.search(nameReg, find_element_by_regex(data_array, nameReg)).group(1)
        platform = find_element_by_regex(data_array, platformReg)
        if platform != None:
            obj['platform'] = re.search(platformReg, platform).group(1)
        else:
            obj['platform'] = 'Any'
        obj['json_path'] = wizardSourcePath + '/' + re.search(jsonmarkcurkipReg, jsonmarkcurkip).group(1) 
        obj['offset'] = jsonmarkcurkipFounded.group(2)
    
    return obj

def reversedHexToInt(hex_string):
    # Разделение строки на двухсимвольные блоки
    split_strings = [hex_string[i:i+2] for i in range(0, len(hex_string), 2)]
    # Разворот блоков
    reversed_strings = split_strings[::-1]
    # Сборка обратно в строку
    reversed_hex_string = ''.join(reversed_strings)
    # Преобразование обратной строки в число
    result = int(reversed_hex_string, 16)
    return result

def add_values(ini):
    for obj in ini:
        values = []
        jsonFile = open(obj['json_path'])
        jsonData = json.load(jsonFile)
        for valueJson in jsonData:
            if not('hex' in valueJson):
                continue
            valueObj = {}
            valueObj['length'] = len(valueJson['hex'])/2
            valueObj['measure'] = None
            valueName = valueJson['name']
            nameAndMeasureReg = r"(\d+)\s*(MHz|mV)"
            nameAndMeasure = re.search(nameAndMeasureReg, valueName)
            if nameAndMeasure != None:
                valueObj['value'] = nameAndMeasure.group(1)
                valueObj['measure'] = nameAndMeasure.group(2)
                valueObj['label'] = None
            else:
                valueObj['value'] = reversedHexToInt(valueJson['hex'])
                valueObj['measure'] = None
                valueObj['label'] = valueName
            values.append(valueObj)
        obj['values'] = values

    return ini

def param_name_to_const_name(name):
    return name.replace(' ', '')

def values_to_ch(values):
    ch_values = []
    for value in values:
        if value['label'] != None:
            ch_values.append('{{{0}, "{1}"}}'.format(value['value'], value['label']))
        else:
            ch_values.append('{{{0}}}'.format(value['value']))
    return ', '.join(ch_values)

def ini_to_ch(ini):
    g = []
    m = []
    e = []
    template = 'const Param {platformLetter}{constName} = {{"{name}", {measure}, {description}, {offset}, {length}, defaultValue, labeled={labeled}, {valuesCount}, {{{values}}}}};'
    for param in ini:
        platformLetter = 'g'
        if param['platform'] == 'Mariko':
            platformLetter = 'm'
        elif param['platform'] == 'Erista':
            platformLetter = 'e'
        constName = param_name_to_const_name(param['name'])
        name = param['name']
        measure = "NULL"
        if param['values'][0]['measure'] != None:
            measure = '"' + param['values'][0]['measure'] + '"'
        description = "NULL" # TODO add description
        offset = param['offset']
        length = int(param['values'][0]['length'])
        labeled = "false"
        if param['values'][0]['label'] != None:
            labeled = "true"
        valuesCount = len(param['values'])
        values = values_to_ch(param['values'])
        if platformLetter == 'm':
            m.append(template.format(platformLetter=platformLetter, constName=constName, name=name, measure=measure, description=description, offset=offset, length=length, labeled=labeled, valuesCount=valuesCount, values=values))
        elif platformLetter == 'e':
            e.append(template.format(platformLetter=platformLetter, constName=constName, name=name, measure=measure, description=description, offset=offset, length=length, labeled=labeled, valuesCount=valuesCount, values=values))
        else:
            g.append(template.format(platformLetter=platformLetter, constName=constName, name=name, measure=measure, description=description, offset=offset, length=length, labeled=labeled, valuesCount=valuesCount, values=values))
    return (m, e, g)

ini_path = sys.argv[1]
wizardSourcePath = sys.argv[2]
with open(ini_path, 'r') as file:
    lines = file.readlines()
lines = lines = map(str.strip, lines)

sections = []
section = []
for line in lines:
    if(line == ""):
        if(section != []):
            sections.append(section)
        section = []
    else:
        if(re.match(nameReg, line) or section != []):
            section.append(line)     
if(section != []):
    sections.append(section)  

ini_objects = []
for section in sections:
    ini_objects.append(parse_ini(section, wizardSourcePath))

add_values(ini_objects)
(m, e, g) = ini_to_ch(ini_objects)
print("===============MARIKO===============")
print('\n'.join(m))
print("===============ERISTA===============")
print('\n'.join(e))
print("==============GENERALS==============")
print('\n'.join(g))