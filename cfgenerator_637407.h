/**
* @file cfgenerator_637407.h
* Synthetic description.
* Library that contains functions to generate the tax code
* Detailed description here.
* @version 1.0
* @date 01/05/2015
* @author Pierpaolo Menga
*/

#ifndef CFGENERATOR_637407_H_
#define CFGENERATOR_637407_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/**
* This function calculates the code of the surname
*
* @param[in] org_surname[] The surname that will be coded
* @param[out] coded_surname[] The code of the surname
* @pre org_surname's length >=2
* @pre org_surname is made of capital letters or spaces or '
* @post coded_surname's length is 3 and it's made of 3 chars
*/
void surname2code(const char org_surname[], char coded_surname[]);

/**
* This function calculates the code of the name
*
* @param[in] name[] The name that will be coded
* @param[out] coded_name[] The code of the name
* @pre name's length >=2
* @pre name is made of capital letters or spaces or '
* @post coded_name's length is 3 and it's made of 3 chars
*/
void name2code(const char name[], char coded_name[]);

/**
* This function calculates the code of the date
*
* @param[in] date[] The date that will be coded
* @param[in] sex The sex that will be coded
* @param[out] coded_date[] The code of the date
* @pre sex is 'M' or 'F'
* @pre date's length is 10 chars
* @pre date: day is >0 and <=31, month is >0 and <=12, year is >1900 and <=2015
* @pre date's format is DD/MM/YYYY
* @post coded_date's length is 5
* @post coded_date is made of 2 numbers (0-9), 1 capital letter and 2 numbers (0-9)
*/
void date2code(const char date[], const char sex, char coded_date[]);

/**
* This function calculates the code of the date
*
* @param[in] coded_surname[] the code of the surname of the tax code
* @param[in] coded_name[] the code of the name of the tax code
* @param[in] coded_date[] the code of the date of the tax code
* @param[in] coded_birth_place[] the code of the birth place of the tax code
* @return control_code the control code of the tax code
* @pre coded_surname's length is 3 and it's made of 3 chars
* @pre coded_name's length is 3 and it's made of 3 chars
* @pre coded_date's length is 5
* @pre coded_date is made of 2 numbers (0-9), 1 capital letter and 2 numbers (0-9)
* @pre coded_birth_place is length 4 and it is made of 1 capital letter and 3 numbers (0-9)
* @post control_code is a capital letter
*/
char cf_ctrl_code(const char coded_surname[], const char coded_name[], const char coded_date[], const char coded_birth_place[]);

/** This function generate the tax code
* @param[in] surname[] The surname that will be coded
* @param[in] name[] The name that will be coded
* @param[in] date[] The date that will be coded
* @param[in] birth_place_code[] The birth_place_code
* @param[in] sex The sex that will be coded
* @param[out] cf The tax code complete
* @pre surname is made of capital letters or spaces or '
* @pre name is made of capital letters or spaces or '
* @pre birth_place_code is length 4 and it is made of 1 capital letter and 3 numbers (0-9)
* @pre sex is 'M' or 'F'
* @pre date's length is 10 chars
* @pre date: day is >0 and <=31, month is >0 and <=12, year is >1900 and <=2015
* @pre date's format is DD/MM/YYYY
* @pre cf will contain 16 chars
* @post cf is a string of 16 chars and at the first 6 position and 9^, 12^ and last positions there are only capital letters and at the other position there are only numbers (0-9)
*/
void cf_generator(const char surname[], const char name[], const char date[], const char birth_place_code[], const char sex, char cf[]);

#endif /* CFGENERATOR_637407_H_ */

