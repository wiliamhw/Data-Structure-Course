#include <stdio.h>

char get_J(char present, char next);
char get_K(char present, char next);

int main(void) {
    // Present state || Next State
    FILE *in = fopen("input.txt", "r");

    // Ja|Ka Jb|Kb Jc|Kc Jd|kd
    FILE *out = fopen("output.txt", "w");

    int N = 16; // banyak data
    int digit = 4; // Banyak bit

    // Penyimpan input
    char present[digit], next[digit];
    char _J, _K;

    for (int i = 0; i < 16; i++) {
        fscanf(in, "%s %s", present, next);

        // Proses
        for (int j = 0; j < digit; j++) {
            _J = get_J(present[j], next[j]);
            _K = get_K(present[j], next[j]);
            fprintf(out, "%c|%c  ", _J, _K);
        }
       fputs("\n", out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

char get_J(char present, char next) {
    if (present == '0') {
        if (next == '0')
            return '0';
        else
            return '1';
    }
    else {
        return 'X';
    }
}

char get_K(char present, char next) {
    if (present == '1') {
        if (next == '0')
            return '1';
        else
            return '0';
    }
    else {
        return 'X';
    }
}