/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include "semantics.h"

#include <stdlib.h>
#include <string.h>

#include "error.h"

extern SymTab *symtab;
extern Token *currentToken;

// Find object with name in symtab table (the whole program)
Object *lookupObject(char *name) {
    Scope *scope = symtab->currentScope;
    Object *obj;

    while (scope != NULL) {
        obj = findObject(scope->objList, name);
        if (obj != NULL)
            return obj;
        scope = scope->outer;
    }
    obj = findObject(symtab->globalObjectList, name);
    if (obj != NULL)
        return obj;
    return NULL;
}

// Check if ident is fresh or not in current scope
void checkFreshIdent(char *name) {
    if (findObject(symtab->currentScope->objList, name) != NULL)
        error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

// Check if ident if fresh or not in the whole program
Object *checkDeclaredIdent(char *name) {
    Object *obj = lookupObject(name);
    if (obj == NULL) {
        error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
    }
    return obj;
}

// Check if constant value is fresh or not in the whole program
Object *checkDeclaredConstant(char *name) {
    // Check fresh
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
    // Check kind is as expected or not
    if (obj->kind != OBJ_CONSTANT)
        error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);

    return obj;
}

// Check if type is fresh or not in the whole program
Object *checkDeclaredType(char *name) {
    // Check fresh
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
    // Check kind
    if (obj->kind != OBJ_TYPE)
        error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);

    return obj;
}

// Check variable
Object *checkDeclaredVariable(char *name) {
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    if (obj->kind != OBJ_VARIABLE)
        error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);

    return obj;
}

// Check function
Object *checkDeclaredFunction(char *name) {
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
    if (obj->kind != OBJ_FUNCTION)
        error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);

    return obj;
}

// Check procedure
Object *checkDeclaredProcedure(char *name) {
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
    if (obj->kind != OBJ_PROCEDURE)
        error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);

    return obj;
}

Object *checkDeclaredLValueIdent(char *name) {
    Object *obj = lookupObject(name);
    if (obj == NULL)
        error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);

    switch (obj->kind) {
        case OBJ_VARIABLE:
        case OBJ_PARAMETER:
            break;
        case OBJ_CONSTANT:
            error(ERR_CONSTANT_ASSIGN, currentToken->lineNo, currentToken->colNo);
            break;
        case OBJ_FUNCTION:
            if (obj != symtab->currentScope->owner)
                error(ERR_INVALID_IDENT, currentToken->lineNo, currentToken->colNo);
            break;
        default:
            error(ERR_INVALID_IDENT, currentToken->lineNo, currentToken->colNo);
    }

    return obj;
}

// Check if type valid or not
void checkIntType(Type *type) {
    // TODO
    if (type != NULL && type->typeClass == TP_INT)
        return;
    else
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
}

void checkCharType(Type *type) {
    // TODO
    if (type != NULL && type->typeClass == TP_CHAR)
        return;
    else
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
}

void checkBasicType(Type *type) {
    // TODO
    if ((type != NULL) && ((type->typeClass == TP_INT) || (type->typeClass == TP_CHAR)))
        return;
    else
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
}

void checkArrayType(Type *type) {
    // TODO
    if ((type != NULL) && (type->typeClass == TP_ARRAY))
        return;
    else
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
}

void checkTypeEquality(Type *type1, Type *type2) {
    // TODO
    if (compareType(type1, type2) == 0)
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
}
