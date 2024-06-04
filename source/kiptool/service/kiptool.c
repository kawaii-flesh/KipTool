#include "kiptool.h"

int _isChangesApplied = 1;

int isChangesApplied() { return _isChangesApplied; }

void setIsChangesApplied(int status) {
    if (_isChangesApplied != status) _isChangesApplied = status;
}
