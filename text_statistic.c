#include "base.h"

typedef struct text_statistic_s {
    int chars;
    int letters;
    int digits;
    int linebreaks;
    int sentences;
} TextStatistic;

typedef bool (*CharacterTestFunction)(char);

//writing the predicate functions
bool is_valid_char(char chr ) {
    if((chr > 31 && chr < 127) ||
        chr == ' '           ||
        chr == '\t'          ||
        chr == '\n'          ||
        chr == '\r') {
        return 1;
    }
    return 0;
}

bool is_letter(char chr) {
    if( (chr > 64 && chr < 91) ||
        (chr > 96 && chr < 123)) {
            return 1;
        }
    return 0;
}
bool is_digit(char chr) {
    if(chr > 47 && chr < 58) {
        return 1;
    }
    return 0;
}
//returns true for ' ' '\n' '\t' '\r' 
bool is_newline(char chr) {
    if(chr == '\n') {
        return 1;
    }
    return 0;
}
//returns true for '.' '!' '?'
bool is_sentence_end(char chr) {
    if((chr == 46) || (chr == 33) || (chr == 63)) {
        return 1;
    }
    return 0;
}
int calculate_statistic(const char * text, CharacterTestFunction predicate) {
    int counter = 0;
    for(int i = 0; text[i] != '\0'; i++) {
        if(predicate(text[i])) {
            counter++;
        }
    }
    return counter;
}

TextStatistic make_text_statistic(String text) {
    TextStatistic *Stats = xcalloc(1, sizeof(TextStatistic));
    Stats->chars = calculate_statistic(text, &is_valid_char);
    
    Stats->letters = calculate_statistic(text, &is_letter);
    Stats->digits = calculate_statistic(text, &is_digit);
    Stats->linebreaks = calculate_statistic(text, &is_newline);
    Stats->sentences = calculate_statistic(text, &is_sentence_end);
    
    return (*Stats);
}

void print_text_statistic(TextStatistic statistic) {
    printf(".chars = %d\n", statistic.chars);
    printf(".letters = %d\n", statistic.letters);
    printf(".digits = %d\n", statistic.digits);
    printf(".linebreaks = %d\n", statistic.linebreaks);
    printf(".sentences = %d\n", statistic.sentences);
}

void test_text_statistic(String text, int chars, int letters, int digits, int linebreaks, int sentences) {
    TextStatistic s = make_text_statistic(text);
    test_equal_i(s.chars, chars);
    test_equal_i(s.letters, letters);
    test_equal_i(s.digits, digits);
    test_equal_i(s.linebreaks, linebreaks);
    test_equal_i(s.sentences, sentences);
}

int main(void) {

    test_text_statistic("", 0, 0, 0, 0, 0);
    test_text_statistic("Hello World.", 12, 10, 0, 0, 1);
    test_text_statistic("Number 12. Number 11?", 21, 12, 4, 0, 2);
    test_text_statistic("This is another text\nwith linebreaks. And sentences!", 52, 43, 0, 1, 2);
    return 0;
}
