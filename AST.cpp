/**
 * @file AST.cpp
 * @brief Implementation of the AST class
 */


#include "AST.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

AST::AST()
{
	root = NULL;
}

AST::~AST()
{
	destroy_tree();
}

void AST::destroy_tree(node *leaf)
{
	if(leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

node *AST::search(int key, node *leaf)
{
	if(leaf != NULL) {
		if(key == leaf->key_value)
			return leaf;
		if(key < leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}

void AST::insert(char const **key, node *leaf)
{
	int i;
	int params = 0;
	int firstOp;

	//set up node for first function name hit
	//could be a function aside from main. will change to deal with that
	if (strncmp(key[0], "main", 4) == 0) {
		leaf->left = new node;
		leaf->left->Type = Main;
		leaf->left->left = NULL;    
		leaf->left->right = NULL;   
	}
	//count up params until first operator is hit
	for (i = 1; i < 3; i++) {
		if (strncmp(key[i], "return", 6) == 0) {//count until operator is hit
			firstOp = i;
			break;
		}
		params++;
	}

	if (params == 0) {
		leaf->left->right = new node;
		leaf = leaf->left->right;
		leaf->Type = Return; //change the logic if other ops are encountered instead
		leaf->left = NULL; //return has one child only; will change for other kinds of ops
	} else {
		//this block for setting up passed in params on left side of tree
	}

	for (i = (firstOp + 1); i < 3; i++) {
		char *end;
		long num = strtol(key[i], &end, 10); 
		//numbers      
		if (end != key[i]) {
			leaf->left = new node;
			leaf = leaf->left;
			leaf->Type = NumberValue;
			leaf->key_value = (int) num;
		} else {
			//more operators
			//more functions
		}
	}
}

void AST::insert(char const **key)
{
	root = new node;
	root->Type = Program;
	root->left = NULL;
	root->right = NULL;
	insert(key, root);
}

node *AST::search(int key)
{
	return search(key, root);
}

void AST::postorder() {
	postorder(root);
}

void AST::postorder(node *leaf)
{
	if (leaf != NULL) {   
		postorder(leaf->left);
		postorder(leaf->right);
		if (leaf->Type == 8)
			printf("%d\n", leaf->key_value);
		else 
			printf("%s\n", leaf->ASTTypes[leaf->Type]);
	}
}

void AST::destroy_tree()
{
	destroy_tree(root);
}
