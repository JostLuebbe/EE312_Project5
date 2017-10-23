/*
 * Set ADT
 * Project5.c 
 *
 * Jost Luebbe
 * Tues - Thurs 11-12:30
 * Fall 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
/*	for(int i=0; i<self->len; i++){
		if(self->elements[i]==x){
			return true;
		}
	}
	return false;*/
	int mid = 0;
	int start = 0;
	int end = self->len-1;
	while(start <= end){
		mid = (start + end) / 2;
		if(x == self->elements[mid]){
			return true;
		}
		if(x < self->elements[mid]){
			end = mid - 1;
			continue;
		}
		else{
			start = mid + 1;
		}
	}
	return false;
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elements[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	if(isMemberSet(self, x)){
		return;
	}
	else{
        if(self->len==0){
            createSingletonSet(self, x);
        }
        else{
            //Set* new_set = (Set*)malloc(sizeof(Set));
            int* new_elements = (int*)malloc(sizeof(int) * (self->len+1));
            int i = self->len;
            while(self->elements[i-1]>x){
                new_elements[i] = self->elements[i-1];
                i--;
            }
            new_elements[i] = x;
            i--;
            while(i>=0){
                new_elements[i] = self->elements[i];
                i--;
            }
            //int* temp = self->elements;
            destroySet(self);
            //displaySet(self
            self->elements = new_elements;
            self->len += 1;
            //free(temp);
            //destroySet(self);
        }
	}
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if(isMemberSet(self, x)){
        int i = 0;
        int y = 0;
        while(i < self->len-1){
            if(self->elements[i] == x){
                self->elements[i] = self->elements[i+1];
                i += 2;
                y=1;
            }
            else{
                self->elements[i] = self->elements[i+y];
                i++;
            }
        }
        self->len = self->len - 1;
    }
    else{
        return;
    }
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}\n");
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len){
        return false;
    }
    int i = 0;
    while(i<self->len){
        if(self->elements[i] != other->elements[i]){
            return false;
        }
        i++;
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(isEmptySet(self)){
        return true;
    }
    if(isEmptySet(other) and !isEmptySet(self)){
        return false;
    }
    if(isEmptySet(self) and isEmptySet(other)){
        return true;
    }
    int i;
    for(i=0; i<self->len; i++){
        if(!isMemberSet(other, self->elements[i])){
            return false;
        }
    }
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int i;
    while(i<self->len){
        if(!isMemberSet(other, self->elements[i])) {
            removeSet(self, self->elements[i]);
            i++;
        }
    }
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    int i = 0;
    while(i<self->len){
        if(isMemberSet(other, self->elements[i])){
            removeSet(self, self->elements[i]);
            i++;
        }
    }
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    int i;
    for(i=0; i<other->len; i++){
        insertSet(self, other->elements[i]);
    }
}
