/* Jonathan Kramer */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRSIZE 30

typedef struct {
	int bibnum;
	char lastname[STRSIZE];
	char firstname[STRSIZE];
	int grade;
	char team[STRSIZE];
	char state[STRSIZE];
	int minutes;
	char semicolon;
	float seconds;
	float pace;
	int rank;
	int rank_gender;
} race_t;

void printheader(void);
void printmenu(void);

int main (void)

{

/************************************* Variables ****************************************/

int i, j, k, a, b, c, x, y, found, answer, answer_p;
float time, distance, pace;
char search_firstname[STRSIZE], search_lastname[STRSIZE];
int menu_option;

race_t boys, girls;

race_t *boysrace;
race_t *girlsrace;
race_t *combinedrace;
race_t hold_value;

FILE *boyfile;
FILE *girlfile;
FILE *new;

new = fopen("data.txt", "w");
boyfile = fopen("20121006.boys.txt", "r");
girlfile = fopen("20121006.girls.txt", "r");

printf("Enter the distance of the race in miles >>>");
scanf("%f", &distance);

/****************************** Check if files are open *********************************/

if ((boyfile == NULL) || (girlfile == NULL)) {
	printf("One of the files not found!\n");
	return(-1);
}

/********************* Finds number of structure elements in each file ******************/

i=0;

while(fscanf(boyfile, "%d%s%s%d%s%s%d%c%f", &boys.bibnum, boys.lastname, boys.firstname, &boys.grade, &boys.team, boys.state, &boys.minutes, &boys.semicolon, &boys.seconds) != EOF) {

	i++;
}

j=0;

while(fscanf(girlfile, "%d%s%s%d%s%s%d%c%f", &girls.bibnum, girls.lastname, girls.firstname, &girls.grade, &girls.team, girls.state, &girls.minutes, &girls.semicolon, &girls.seconds) != EOF) {

	j++;
}

k=i+j;

/******************** Dynamically allocates arrays of structure race_t ******************/

boysrace = (race_t*)malloc(i * sizeof(race_t));
girlsrace = (race_t*)malloc(j * sizeof(race_t));
combinedrace = (race_t*)malloc(k * sizeof(race_t));

fclose(boyfile);
fclose(girlfile);
boyfile = fopen("20121006.boys.txt", "r");
girlfile = fopen("20121006.girls.txt", "r");

/******************* Puts values from files into array of structures ********************/

i=0;

while(fscanf(boyfile, "%d%s%s%d%s%s%d%c%f", &boysrace[i].bibnum, boysrace[i].lastname, boysrace[i].firstname, &boysrace[i].grade, &boysrace[i].team, boysrace[i].state, &boysrace[i].minutes, &boysrace[i].semicolon, &boysrace[i].seconds) != EOF) {

	i++;
}

j=0;

while(fscanf(girlfile, "%d%s%s%d%s%s%d%c%f", &girlsrace[j].bibnum, girlsrace[j].lastname, girlsrace[j].firstname, &girlsrace[j].grade, &girlsrace[j].team, girlsrace[j].state, &girlsrace[j].minutes, &girlsrace[j].semicolon, &girlsrace[j].seconds) != EOF) {

	j++;
}

fclose(boyfile);
fclose(girlfile);

boyfile = fopen("20121006.boys.txt", "r");
girlfile = fopen("20121006.girls.txt", "r");

a=0;

while(a<i) {
	fscanf(boyfile, "%d%s%s%d%s%s%d%c%f", &combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, &combinedrace[a].grade, &combinedrace[a].team, combinedrace[a].state, &combinedrace[a].minutes, &combinedrace[a].semicolon, &combinedrace[a].seconds);
	a++;
}

a=i;

while(a<k) {
	fscanf(girlfile, "%d%s%s%d%s%s%d%c%f", &combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, &combinedrace[a].grade, &combinedrace[a].team, combinedrace[a].state, &combinedrace[a].minutes, &combinedrace[a].semicolon, &combinedrace[a].seconds);
	a++;
}

/* for(a=0; a<k; a++) {
printf("%d %s %s %d %s %s %d%c%04.1f\n", combinedrace[a].bibnum, combinedrace[a].firstname, combinedrace[a].lastname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds);
}
printf("%d", k); */

fclose(boyfile);
fclose(girlfile);


/****************************************************************************************/
/****************************************************************************************/
/************************************ DO-WHILE LOOP *************************************/
/****************************************************************************************/
/****************************************************************************************/

do {

printmenu();

/******************************* Putting in time order **********************************/

for (a=0; a < (k-1); a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].minutes < combinedrace[b-1].minutes){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

for (a=0; a < (k-1); a++) {
	
	for(b=1; b < k; b++) {	
	
		if ((combinedrace[b].minutes == combinedrace[b-1].minutes) && (combinedrace[b].seconds < combinedrace[b-1].seconds)) {
		
			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

/*********************************** Finding the Pace ***********************************/

/****** boys race ******/
for (b=0; b<i; b++) {
	time = (float)boysrace[b].minutes + ((boysrace[b].seconds)/60);
	pace = (time / distance);
	boysrace[b].pace = pace;
}

/****** girls race ******/
for (b=0; b<j; b++) {
	time = (float)girlsrace[b].minutes + ((girlsrace[b].seconds)/60);
	pace = (time / distance);
	girlsrace[b].pace = pace;
}

/****** combined race ******/
for (b=0; b<k; b++) {
	time = (float)combinedrace[b].minutes + ((combinedrace[b].seconds)/60);
	pace = (time / distance);
	combinedrace[b].pace = pace;
}


/************************************ Rankings ******************************************/

x=0;
y=1;

/* combined */

while (x<k) {
	combinedrace[x].rank = y;
	x++;
	y++;
}

x=0;
y=1;

/* boys */

while (x<k) {
	boysrace[x].rank = y;
	x++;
	y++;
}

x=0;
y=1;

/* girls */

while (x<k) {
	girlsrace[x].rank = y;
	x++;
	y++;
}

for(x=0; x<k; x++) {

	for(y=0; y<j; y++) {	
		if (combinedrace[x].bibnum == girlsrace[y].bibnum) {
			combinedrace[x].rank_gender = girlsrace[y].rank;
		}
	}
	for(y=0; y<i; y++) {
		if (combinedrace[x].bibnum == boysrace[y].bibnum) {
			combinedrace[x].rank_gender = boysrace[y].rank;
		}
	}
}

/****************************************************************************************/
/****************************************************************************************/
/************************************** SWITCH ******************************************/
/****************************************************************************************/
/****************************************************************************************/

scanf("%d", &menu_option);

switch(menu_option) {

/****************************************************************************************/
/************************************* Listing ******************************************/
/****************************************************************************************/

/*********************************** List Overall ***************************************/

case 1: 

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < (k-1); a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].minutes < combinedrace[b-1].minutes){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}	
	
for (a=0; a < (k-1); a++) {	
	
	for(b=1; b < k; b++) {	
	
		if ((combinedrace[b].minutes == combinedrace[b-1].minutes) && (combinedrace[b].seconds < combinedrace[b-1].seconds)) {
		
			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < (k-1); a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].minutes < combinedrace[b-1].minutes){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

for (a=0; a < (k-1); a++) {
	
	for(b=1; b < k; b++) {	
	
		if ((combinedrace[b].minutes == combinedrace[b-1].minutes) && combinedrace[b].seconds < combinedrace[b-1].seconds) {
		
			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

}

break;

/********************************** List boys only **************************************/

case 2:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < i-1; a++) {

	for(b=1; b < i; b++) {
		
		if (boysrace[b].minutes < boysrace[b-1].minutes){

			hold_value = boysrace[b-1];
			boysrace[b-1] = boysrace[b];
			boysrace[b] = hold_value;
		}
		if ((boysrace[b].minutes == boysrace[b-1].minutes) && boysrace[b].seconds < boysrace[b-1].seconds) {
		
			hold_value = boysrace[b-1];
			boysrace[b-1] = boysrace[b];
			boysrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<i; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", boysrace[a].bibnum, boysrace[a].lastname, boysrace[a].firstname, boysrace[a].grade, boysrace[a].team, boysrace[a].state, boysrace[a].minutes, boysrace[a].semicolon, boysrace[a].seconds, boysrace[a].pace, boysrace[a].rank, boysrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < i-1; a++) {

	for(b=1; b < i; b++) {
		
		if (boysrace[b].minutes < boysrace[b-1].minutes){

			hold_value = boysrace[b-1];
			boysrace[b-1] = boysrace[b];
			boysrace[b] = hold_value;
		}
		if ((boysrace[b].minutes == boysrace[b-1].minutes) && boysrace[b].seconds < boysrace[b-1].seconds) {
		
			hold_value = boysrace[b-1];
			boysrace[b-1] = boysrace[b];
			boysrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<i; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", boysrace[a].bibnum, boysrace[a].lastname, boysrace[a].firstname, boysrace[a].grade, boysrace[a].team, boysrace[a].state, boysrace[a].minutes, boysrace[a].semicolon, boysrace[a].seconds, boysrace[a].pace, boysrace[a].rank, boysrace[a].rank_gender);
}

break;
}

break;

/********************************* List girls only **************************************/

case 3:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < (j-1); a++) {

	for(b=1; b < j; b++) {
		
		if (girlsrace[b].minutes < girlsrace[b-1].minutes){

			hold_value = girlsrace[b-1];
			girlsrace[b-1] = girlsrace[b];
			girlsrace[b] = hold_value;
		}
	}	
}
		
for (a=0; a<j; a++) {	
	
	for (b=1; b<j; b++) {	
	
		if ((girlsrace[b].minutes == girlsrace[b-1].minutes) && girlsrace[b].seconds < girlsrace[b-1].seconds) {
		
			hold_value = girlsrace[b-1];
			girlsrace[b-1] = girlsrace[b];
			girlsrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<j; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", girlsrace[a].bibnum, girlsrace[a].lastname, girlsrace[a].firstname, girlsrace[a].grade, girlsrace[a].team, girlsrace[a].state, girlsrace[a].minutes, girlsrace[a].semicolon, girlsrace[a].seconds, girlsrace[a].pace, girlsrace[a].rank, girlsrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < j-1; a++) {

	for(b=1; b < j; b++) {
		
		if (girlsrace[b].minutes < girlsrace[b-1].minutes){

			hold_value = girlsrace[b-1];
			girlsrace[b-1] = girlsrace[b];
			girlsrace[b] = hold_value;
		}
		if ((girlsrace[b].minutes == girlsrace[b-1].minutes) && girlsrace[b].seconds < girlsrace[b-1].seconds) {
		
			hold_value = girlsrace[b-1];
			girlsrace[b-1] = girlsrace[b];
			girlsrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<j; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", girlsrace[a].bibnum, girlsrace[a].lastname, girlsrace[a].firstname, girlsrace[a].grade, girlsrace[a].team, girlsrace[a].state, girlsrace[a].minutes, girlsrace[a].semicolon, girlsrace[a].seconds, girlsrace[a].pace, girlsrace[a].rank, girlsrace[a].rank_gender);
}

break;
}

break;

/********************************* List by school ***************************************/

case 4:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].team, combinedrace[b-1].team) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].team, combinedrace[b-1].team) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;
}

break;

/********************************** List by grade ***************************************/

case 5:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].grade < combinedrace[b-1].grade){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}	
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].grade < combinedrace[b-1].grade){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}	
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;
}

break;

/********************************** List by state ***************************************/

case 6:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].state, combinedrace[b-1].state) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].state, combinedrace[b-1].state) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;
}

break;

/****************************************************************************************/
/************************************** Sorting *****************************************/
/****************************************************************************************/

/********************************* Sort by last name ************************************/

case 7:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].lastname, combinedrace[b-1].lastname) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].lastname, combinedrace[b-1].lastname) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;
}

break;

/********************************* Sort by first name ***********************************/

case 8:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].firstname, combinedrace[b-1].firstname) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].firstname, combinedrace[b-1].firstname) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}
break;

}

break;

/********************************* Sort by school ***************************************/

case 9:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].team, combinedrace[b-1].team) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}
printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].team, combinedrace[b-1].team) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}
printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}
break;
}
break;

/********************************** Sort by state ***************************************/

case 10:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].state, combinedrace[b-1].state) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (strcmp(combinedrace[b].state, combinedrace[b-1].state) < 0) {

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;

		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}
break;
}
break;


/************************************ Sort by time **************************************/

case 11:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].minutes < combinedrace[b-1].minutes){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
		if ((combinedrace[b].minutes == combinedrace[b-1].minutes) && combinedrace[b].seconds < combinedrace[b-1].seconds) {
		
			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].minutes < combinedrace[b-1].minutes){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
		if ((combinedrace[b].minutes == combinedrace[b-1].minutes) && combinedrace[b].seconds < combinedrace[b-1].seconds) {
		
			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;
}
break;

/************************************ Sort by grade *************************************/

case 12:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].grade < combinedrace[b-1].grade){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}	
}

printheader();

for(a=0; a<k; a++) {
	fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

case 0:

for (a=0; a < k-1; a++) {

	for(b=1; b < k; b++) {
		
		if (combinedrace[b].grade < combinedrace[b-1].grade){

			hold_value = combinedrace[b-1];
			combinedrace[b-1] = combinedrace[b];
			combinedrace[b] = hold_value;
		}
	}	
}

printheader();

for(a=0; a<k; a++) {
	printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d           %3d \n", combinedrace[a].bibnum, combinedrace[a].lastname, combinedrace[a].firstname, combinedrace[a].grade, combinedrace[a].team, combinedrace[a].state, combinedrace[a].minutes, combinedrace[a].semicolon, combinedrace[a].seconds, combinedrace[a].pace, combinedrace[a].rank, combinedrace[a].rank_gender);
}

break;

}

break;

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

/************************************* Searching ****************************************/

case 13:

printf("Print output to file? (type '1' for yes and '0' for no) >>>");
scanf("%d", &answer_p);

switch (answer_p) {

case 1:

printf("Enter the name of the runner >>> ");
scanf("%s %s", search_firstname, search_lastname);

found = 0;

b=0;

while ((b < k-1) && (!found)) {

	if ((strcmp(search_firstname, combinedrace[b].firstname) == 0) && (strcmp(search_lastname, combinedrace[b].lastname) == 0)) {
		found = 1;
		printf("\n");
		printheader();
		fprintf(new, "  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d        %3d \n", combinedrace[b].bibnum, combinedrace[b].firstname, combinedrace[b].lastname, combinedrace[b].grade, combinedrace[b].team, combinedrace[b].state, combinedrace[b].minutes, combinedrace[b].semicolon, combinedrace[b].seconds), combinedrace[b].pace, combinedrace[b].rank, combinedrace[b].rank_gender;
	}
	b++;
}

break; 

case 0:

printf("Enter the name of the runner >>> ");
scanf("%s %s", search_firstname, search_lastname);

found = 0;

b=0;

while ((b < k-1) && (!found)) {

	if ((strcmp(search_firstname, combinedrace[b].firstname) == 0) && (strcmp(search_lastname, combinedrace[b].lastname) == 0)) {
		found = 1;
		printf("\n");
		printheader();
		printf("  %4d   %-16s    %-10s  %2d      %-18s %2s     %2d%1c%04.1f    %7.4f       %3d        %3d \n", combinedrace[b].bibnum, combinedrace[b].firstname, combinedrace[b].lastname, combinedrace[b].grade, combinedrace[b].team, combinedrace[b].state, combinedrace[b].minutes, combinedrace[b].semicolon, combinedrace[b].seconds), combinedrace[b].pace, combinedrace[b].rank, combinedrace[b].rank_gender;
	}
	b++;
}

break; 
}
break;

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

}

printf("Do you want to return to the menu? (type '1' for yes and '0' for no) >>> ");
scanf("%d", &answer);
printf("\n"); 

} while (answer == 1);

/********************************* Free allocated memory ********************************/

free(boysrace);
free(girlsrace);
free(combinedrace);

return(0);

}

void printheader(void)

{

printf("\n\n\n|------+------------------+-----------+-------+------------------+-------+----------+----------+--------------+-------------|\n");
printf("| BIB# |     LASTNAME     | FIRSTNAME | GRADE |       TEAM       | STATE |   TIME   |   PACE   | RANK:OVERALL | RANK:GENDER |\n");
printf("|------+------------------+-----------+-------+------------------+-------+----------+----------+--------------+-------------|\n");

}
								
void printmenu(void)

{
printf("\n\n");								

printf("**********************************************************************\n");
printf("***************************** M  E  N  U *****************************\n");
printf("**********************************************************************\n");

printf("\n\n");								

printf("**********************	**********************	**********************\n");
printf("**** LIST RESULTS ****  **** SORT RESULTS ****  ***  SEARCH RUNNER ***\n");
printf("**********************  **********************  **********************\n");

printf("\n");	

printf("  (1) Combined            (7) By last name            (13) Search       \n\n");    

printf("  (2) Boys Only           (8) By first name\n\n");

printf("  (3) Girls Only          (9) By school\n\n");

printf("  (4) School             (10) By state\n\n");

printf("  (5) Grade              (11) By time\n\n");

printf("  (6) State              (12) By grade\n\n");

printf("\n");	

printf("Type the appropriate character in parenthesis to select an option from the menu >>>");

printf("\n\n");	

}















