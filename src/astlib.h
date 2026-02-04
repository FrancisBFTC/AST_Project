#ifndef _ASTLIB_H_
#define _ASTLIB_H_

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

const char *input;

typedef enum {
    NODE_NUM,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV
} NodeType;

typedef struct AST {
    NodeType type;
    int value;
    struct AST *left;
    struct AST *right;
} AST;

AST *parse_expr();
AST *parse_term();
AST *parse_factor();

AST *new_node(NodeType type, int value, AST *left, AST *right) {
    AST *node = malloc(sizeof(AST));
    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}


void skip_spaces() {
    while (*input == ' ')
        input++;
}


int parse_number() {
    int value = 0;
    while (*input >= '0' && *input <= '9') {
        value = value * 10 + (*input - '0');
        input++;
    }
    return value;
}


AST *parse_factor() {
    skip_spaces();

    if (*input == '(') {
        input++;
        AST *node = parse_expr();
        skip_spaces();
        input++;
        return node;
    }

    int value = parse_number();
    return new_node(NODE_NUM, value, NULL, NULL);
}


AST *parse_term() {
    AST *node = parse_factor();

    while (1) {
        skip_spaces();

        if (*input == '*') {
            input++;
            node = new_node(NODE_MUL, 0, node, parse_factor());
        } else if (*input == '/') {
            input++;
            node = new_node(NODE_DIV, 0, node, parse_factor());
        } else {
            break;
        }
    }

    return node;
}


AST *parse_expr() {
    AST *node = parse_term();

    while (1) {
        skip_spaces();

        if (*input == '+') {
            input++;
            node = new_node(NODE_ADD, 0, node, parse_term());
        } else if (*input == '-') {
            input++;
            node = new_node(NODE_SUB, 0, node, parse_term());
        } else {
            break;
        }
    }

    return node;
}


AST *parse(const char *str) {
    input = str;
    return parse_expr();
}


int eval(AST *node) {
    switch (node->type) {
        case NODE_NUM: return node->value;
        case NODE_ADD: return eval(node->left) + eval(node->right);
        case NODE_SUB: return eval(node->left) - eval(node->right);
        case NODE_MUL: return eval(node->left) * eval(node->right);
        case NODE_DIV: return eval(node->left) / eval(node->right);
    }
    return 0;
}

#endif
