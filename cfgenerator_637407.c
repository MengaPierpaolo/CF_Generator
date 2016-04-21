/**
* @file cfgenerator_637407.c
* @version 1.0
* @date 01/05/2015
* @author Pierpaolo Menga
*/


#include "cfgenerator_637407.h"

static bool is_valid_name_or_surname(const char string[50]){
	int n; //number of characters
	bool valid=true;
	n=strlen(string);
	for (int i=0; i<n; i++){
		valid&=(string[i]>='A' || string[i]<='Z' || string[i]==' ' || string[i]==39);
	}
	return valid;
}

static bool is_valid_code(const char code[4]){
	bool valid=true;

	valid&=(strlen(code)==3);

	for (int i=0; i<3; i++){
		valid&=(code[i]>='A' || code[i]<='Z');
	}

	return valid;
}

/**
* This function calculates the code of the surname following the rules to calculate the Italy's tax code
*/
void surname2code(const char org_surname[], char coded_surname[]){
	strcpy(coded_surname,"   ");  // initialize  code name

	// pre-conditions
	assert(strlen(org_surname)>=2);
	assert(is_valid_name_or_surname(org_surname));

	// LOCAL VARS
	int i,j; // counters
	int p=0; // index of position
	char vocali[6]="AEIOU"; // vocals string
	int n; // surname's length
	int t; // control test

	coded_surname[3]='\0';

	n=strlen(org_surname);  // count surname's number of letters

	if(org_surname[2]==39) n--;

	if(n==2){ // if the surname is made with 2 letters
		for(i=0; i<n; i++){
			t=0;
			for(j=0; j<5; j++){
				if(org_surname[i]==vocali[j]){
					t=1;
					break; // i've find the vocal
				}
				if(org_surname[i]==' ' || org_surname[i]==39){
					t=1;
				}
			}
			if(t==0){ // if i've not found spaces or vocals
				coded_surname[p]=org_surname[i];
				p++;
			}
		}
		if(p<=2){
			for(i=0; i<n; i++){
				t=0;
				for(j=0; j<5; j++){
					if(org_surname[i]==vocali[j]){
						t=1;
						break;
					}
				}
				if(t==1){
					coded_surname[p]=org_surname[i];
					p++;
					break;
				}
			}
		}
		coded_surname[2]='X'; // assign 'X' at the 3^ position of the code
		p++;
	}
	else{ // if the surname is made with more than 2 letters
		for(i=0; i<n; i++){
			t=0;
			for(j=0; j<5; j++){
				if(org_surname[i]==vocali[j]){
					t=1;
					break; // i've find a vocal
				}
				if(org_surname[i]==' ' || org_surname[i]==39) t=1;
			}
			if(t==0){
				coded_surname[p]=org_surname[i];
				p++;
			}
			if(p==3) break;
		}
		if(p<=2){
			for(i=0; i<n; i++){
				t=0;
				for(j=0; j<5; j++){
					if(org_surname[i]==vocali[j]){
						t=1;
						break;
					}
				}
				if(t==1){
					coded_surname[p]=org_surname[i];
					p++;
				}
				if(p==3) break;
			}
		}
	}
	// post-conditions
	assert(is_valid_code(coded_surname));

} //end function codice_cognome

/**
* This function calculates the code of the name following the rules to calculate the Italy's tax code
*/
void name2code(const char name[], char coded_name[]){
	strcpy(coded_name,"   "); // initialize  code name

	// pre-conditions
	assert(strlen(name)>=2);
	assert(is_valid_name_or_surname(name));

	// LOCAL VARS
	int i,j; // counters
	int p=0; // index of position
	char vocali[6]="AEIOU"; // vocals string
	int n; // name's length
	int t; // control test
	int c=0; // number of consonant

	n=strlen(name); // count name's number of letters

	if(name[2]==39) n--;

	for(i=0; i<n; i++){ // count consonants
		t=0;
		for(j=0; j<5; j++){
			if(name[i]==vocali[j]){
				t=1;
				break;
			}
			if(name[i]==' ' || name[i]==39) t=1;
		}
		if(t==0) c++; // increment number of consonants
	}
	if(c<=3){ // if the  consonants are 3 or less
		if(n==2){ // if the name is made with 2 letters
			for(i=0; i<n; i++){
				t=0;
				for(j=0; j<5; j++){
					if(name[i]==vocali[j]){
						t=1;
						break;
					}
					if(name[i]==' ' || name[i]==39) t=1;
				}
				if(t==0){
					coded_name[p]=name[i];
					p++;
				}
			}
			if(p<=1){
				for(i=0; i<n; i++){
					t=0;
					for(j=0; j<5; j++){
						if(name[i]==vocali[j]){
							t=1;
							break;
						}
					}
					if(t==1){
						coded_name[p]=name[i];
						p++;
					}
					if(p==2) break;
				}
			}
			coded_name[2]='X'; // assign 'X' at the 3^ position of the code
		}
		else{ // if the name is made with more than 2 letters
			for(i=0; i<n; i++){
				t=0;
				for(j=0; j<5; j++){
					if(name[i]==vocali[j]){
						t=1;
						break;
					}
					if(name[i]==' ' || name[i]==39) t=1;
				}
				if(t==0){
					coded_name[p]=name[i];
					p++;
				}
			}
			if(p<3){
				for(i=0; i<n; i++){
					t=0;
					for(j=0; j<5; j++){
						if(name[i]==vocali[j]){
							t=1;
							break;
						}
					}
					if(t==1){
						coded_name[p]=name[i];
						p++;
					}
					if(p==3) break;
				}
			}
		}
	}
	else{
		c=0; // reset consonants counter
		for(i=0; i<n; i++){
			t=0;
			for(j=0; j<5; j++){
				if(name[i]==vocali[j]){
					t=1;
					break;
				}
				if(name[i]==' ' || name[i]==39) t=1;
			}
			if(t==0){
				c++;
				if(c!=2){ // jump the second consonant
					coded_name[p]=name[i];
					p++;
				}
			}
			if(p==3) break;
		}
	}
	coded_name[3]='\0';

	// post-conditions
	assert(is_valid_code(coded_name));
}

static bool is_valid_date(const char d[]){
	int dd,mm,yyyy;
	bool valid=true;

	dd=(d[0]-'0')*10 + (d[1]-'0');
	mm=(d[3]-'0')*10 + (d[4]-'0');
	yyyy=(d[6]-'0')*1000 + (d[7]-'0')*100 + (d[8]-'0')*10 + (d[9]-'0');

	valid &= (dd>0 && dd<=31);
	valid &= (mm>0 && mm<=12);
	valid &= (yyyy>1900 && yyyy<=2015);

	for(int i=0; i<10; i++){
			valid &= (i==2 || i==5)? (d[i]=='/') : (d[i]>='0' && d[i]<='9');
	}

	return valid;
}

static bool is_valid_coded_date(const char c[]){
	bool valid=true;

	valid &= (strlen(c)==5);

	for(int i=0; i<5; i++){
		valid &= (i==2)? (c[i]>='A' && c[i]<='Z') : (c[i]>='0' && c[i]<='9');
	}
	return valid;
}

/**
* This function calculates the code of the date following the rules to calculate the Italy's tax code
*/
void date2code(const char date[], const char sex, char coded_date[]){
	strcpy(coded_date,"     "); //initialize code date

	// pre-conditions
	assert(sex=='M' || sex=='F');
	assert(strlen(date)==10);
	assert(is_valid_date(date));

	//LOCAL VARS
	char temp[5]; //array temporary
	int m; //integer month

	temp[0]=date[3];
	temp[1]=date[4];
	temp[2]='\0';
	m=atoi(temp); //take the month like an integer

	coded_date[0]=date[8];
	coded_date[1]=date[9];

	switch(m){ //letter of the month
		case 1: coded_date[2]='A'; break;
		case 2: coded_date[2]='B'; break;
		case 3: coded_date[2]='C'; break;
		case 4: coded_date[2]='D'; break;
		case 5: coded_date[2]='E'; break;
		case 6: coded_date[2]='H'; break;
		case 7: coded_date[2]='L'; break;
		case 8: coded_date[2]='M'; break;
		case 9: coded_date[2]='P'; break;
		case 10: coded_date[2]='R'; break;
		case 11: coded_date[2]='S'; break;
		case 12: coded_date[2]='T'; break;
	}

	coded_date[3]=date[0];
	coded_date[4]=date[1];

	if(sex=='F'){ //if the sex is female
		coded_date[3]+=4;
	}

	coded_date[5]='\0';

	// post-conditions
	assert(is_valid_coded_date(coded_date));

}

static bool is_valid_coded_birth_place(const char code[]){
	bool valid=true;

	valid &= (strlen(code)==4);

	valid &= (code[0]>='A' && code[0]<='Z');

	for(int i=1; i<=3; i++){
		valid &= (code[i]>='0' && code[i]<='9');
	}

	return valid;
}

static bool is_valid_ctrl_code(const char c){
	bool valid=true;

	valid &= (c>='A' && c<='Z');

	return valid;
}

/**
* This function calculates the control code following the rules to calculate the Italy's tax code
*/
char cf_ctrl_code(const char coded_surname[], const char coded_name[], const char coded_date[], const char coded_birth_place[]){
	//pre-conditions
	assert(is_valid_code(coded_surname));
	assert(is_valid_code(coded_name));
	assert(is_valid_coded_date(coded_date));
	assert(is_valid_coded_birth_place(coded_birth_place));


	char cod[16]; //the tax code without the last char
	sprintf(cod,"%s%s%s%s\0",coded_surname,coded_name,coded_date,coded_birth_place); //assemble the code
	char control_code;
	int c=0;
	int i; //counters
		for(i=0; i<15; i+=2){ // odd positions
			if(cod[i]=='0' || cod[i]=='A'){ c+=1; }
			else if(cod[i]=='2' || cod[i]=='C'){ c+=5; }
			else if(cod[i]=='3' || cod[i]=='D'){ c+=7; }
			else if(cod[i]=='4' || cod[i]=='E'){ c+=9; }
			else if(cod[i]=='5' || cod[i]=='F'){ c+=13; }
			else if(cod[i]=='6' || cod[i]=='G'){ c+=15; }
			else if(cod[i]=='7' || cod[i]=='H'){ c+=17; }
			else if(cod[i]=='8' || cod[i]=='I'){ c+=19; }
			else if(cod[i]=='9' || cod[i]=='J'){ c+=21; }
			else if(cod[i]=='K'){ c+=2; }
			else if(cod[i]=='L'){ c+=4; }
			else if(cod[i]=='M'){ c+=18; }
			else if(cod[i]=='N'){ c+=20; }
			else if(cod[i]=='O'){ c+=11; }
			else if(cod[i]=='P'){ c+=3; }
			else if(cod[i]=='Q'){ c+=6; }
			else if(cod[i]=='R'){ c+=8; }
			else if(cod[i]=='S'){ c+=12; }
			else if(cod[i]=='T'){ c+=14; }
			else if(cod[i]=='U'){ c+=16; }
			else if(cod[i]=='V'){ c+=10; }
			else if(cod[i]=='W'){ c+=22; }
			else if(cod[i]=='X'){ c+=25; }
			else if(cod[i]=='Y'){ c+=24; }
			else if(cod[i]=='Z'){ c+=23; }
		}
		for(i=1; i<15; i+=2){ // even positions
			if(cod[i]=='1' || cod[i]=='B'){ c+=1; }
			else if(cod[i]=='2' || cod[i]=='C'){ c+=2; }
			else if(cod[i]=='3' || cod[i]=='D'){ c+=3; }
			else if(cod[i]=='4' || cod[i]=='E'){ c+=4; }
			else if(cod[i]=='5' || cod[i]=='F'){ c+=5; }
			else if(cod[i]=='6' || cod[i]=='G'){ c+=6; }
			else if(cod[i]=='7' || cod[i]=='H'){ c+=7; }
			else if(cod[i]=='8' || cod[i]=='I'){ c+=8; }
			else if(cod[i]=='9' || cod[i]=='J'){ c+=9; }
			else if(cod[i]=='K'){ c+=10; }
			else if(cod[i]=='L'){ c+=11; }
			else if(cod[i]=='M'){ c+=12; }
			else if(cod[i]=='N'){ c+=13; }
			else if(cod[i]=='O'){ c+=14; }
			else if(cod[i]=='P'){ c+=15; }
			else if(cod[i]=='Q'){ c+=16; }
			else if(cod[i]=='R'){ c+=17; }
			else if(cod[i]=='S'){ c+=18; }
			else if(cod[i]=='T'){ c+=19; }
			else if(cod[i]=='U'){ c+=20; }
			else if(cod[i]=='V'){ c+=21; }
			else if(cod[i]=='W'){ c+=22; }
			else if(cod[i]=='X'){ c+=23; }
			else if(cod[i]=='Y'){ c+=24; }
			else if(cod[i]=='Z'){ c+=25; }
		}
		c=c%26;
		switch(c){
			case 0: control_code='A'; break;
			case 1: control_code='B'; break;
			case 2: control_code='C'; break;
			case 3: control_code='D'; break;
			case 4: control_code='E'; break;
			case 5: control_code='F'; break;
			case 6: control_code='G'; break;
			case 7: control_code='H'; break;
			case 8: control_code='I'; break;
			case 9: control_code='J'; break;
			case 10: control_code='K'; break;
			case 11: control_code='L'; break;
			case 12: control_code='M'; break;
			case 13: control_code='N'; break;
			case 14: control_code='O'; break;
			case 15: control_code='P'; break;
			case 16: control_code='Q'; break;
			case 17: control_code='R'; break;
			case 18: control_code='S'; break;
			case 19: control_code='T'; break;
			case 20: control_code='U'; break;
			case 21: control_code='V'; break;
			case 22: control_code='W'; break;
			case 23: control_code='X'; break;
			case 24: control_code='Y'; break;
			case 25: control_code='Z'; break;
		}

		//post-conditions
		assert(is_valid_ctrl_code(control_code));

		return control_code;
}

static bool is_valid_cf(const char c[]){
	bool valid=true;

	for(int i=0; i<16; i++){
		valid &= (i<=5 || i==8 || i==11 || i==15)? (c[i]>='A' && c[i]<='Z') : (c[i]>='0' && c[i]<='9');
	}
	return valid;
}

/**
* This function generate Italy's tax code
*/
void cf_generator(const char surname[], const char name[], const char date[], const char birth_place_code[], const char sex, char cf[]){
	strcpy(cf,"                "); //initialize cf

	//pre-conditions
	assert(is_valid_name_or_surname(surname));
	assert(is_valid_name_or_surname(name));
	assert(is_valid_date(date));
	assert(sex=='M' || sex=='F');
	assert(is_valid_coded_birth_place(birth_place_code));

	char c_surname[4],c_name[4],c_date[6];

	//call the functions
	surname2code(surname,c_surname);
	name2code(name,c_name);
	date2code(date,sex,c_date);

	sprintf(cf,"%s%s%s%s%c\0",c_surname,c_name,c_date,birth_place_code,cf_ctrl_code(c_surname,c_name,c_date,birth_place_code)); //assemble the cf

	//post-conditions
	assert(is_valid_cf(cf));
}
