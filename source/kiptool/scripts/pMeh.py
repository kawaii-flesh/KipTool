import sys
import json

import sys
import json

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

def getPmeh(pMehJson, pmeh_index):
    values = []
    for value in pMehJson:
        values.append("{{.value = {0}}}".format(reversedHexToInt(value["hex"])))
    fixedValue = "const FixedValues pMeh{0}FV = {{.valuesCount = {1}, .values = {{{2}}}}};".format(pmeh_index, len(pMehJson), ', '.join(values))
    param = 'const Param pMeh{0} = {{.name = "pMeh {0}", .measure = NULL, .description = NULL, .offset = {0}, .length = 4, .defaultValue = custTable.marikoGpuVoltArray[{0}], .limitsCount = 1, .limits = {{.type = EFixedValues, .values = &pMeh{0}FV}}}};'.format(pmeh_index)
    print(fixedValue)
    print(param)

pmeh_dir = sys.argv[1]
pmeh_count = sys.argv[2]
for i in range(0, int(pmeh_count) + 1):
    with open(pmeh_dir + 'pMeh{}.json'.format(i)) as f:
        pMehJson = json.load(f)
        getPmeh(pMehJson, i)    