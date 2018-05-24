/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "lottery.h"

static char* file_name;
static char separator;
static int* finished_drawing;
static bool is_drawn = false;

bool init_lottery(char* csv_name, char csv_separator){
    FILE* file = fopen(csv_name, "r");
    separator = csv_separator;
    is_drawn = false;
    file_name = csv_name;
    if(file != 0)
    {
      fclose(file);
      return true;
    }
    return false;
}

bool get_tip(int tip, int* array){
    FILE* file = fopen(file_name, "r");
    char input[MAX_LINE_LEN];
    int count = 0;
    if(tip < 0 || file == 0){
        fclose(file);
        return false;
    }
    char* file_array = fgets(input, MAX_LINE_LEN, file);
    while(file_array != 0 && count < tip) {
        file_array = fgets(input, MAX_LINE_LEN, file);
        count++;
        if (file_array != input) {
            fclose(file);
            return false;
        }
    }
    int position = 0;
    while(input[position] != separator && position < UUID_LEN){
        position++;
    }

    int insert_on_possition = 0;
    int tens = 0;
    while(insert_on_possition < 6){
        position++;
        if(input[position] <= '9' && input[position] >= '0'){
            tens = tens * 10 + (input[position] - '0');
        }
        else{
            array[insert_on_possition] = tens;
            tens = 0;
            insert_on_possition++;
        }
    }
    fclose(file);
    return true;
}

bool set_drawing(int* to_draw_array){
    is_drawn = true;
    finished_drawing = to_draw_array;
    return false;
}

int get_tip_result(int tip){
    if(!is_drawn)
    {
      return -1;
    }

    int array[6];
    if(!get_tip(tip, array))
    {
      return -2;
    }

    int count = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(array[i] == finished_drawing[j])
            {
              count++;
            }
        }
    }
    return count;
}

int get_right_tips_count(int tip){
    if(is_drawn && tip >= 0 && tip <= TIP_SIZE)
    {
      int to_check_tip = 0;
      int count = 0;
      int correct_tip_count = 0;
      do{
          correct_tip_count = get_tip_result(to_check_tip);
          if(correct_tip_count == tip)
          {
            count++;
          }
          to_check_tip++;
      }while (correct_tip_count != -2 && correct_tip_count != -1);
      return count;
    }
    return -1;
}
