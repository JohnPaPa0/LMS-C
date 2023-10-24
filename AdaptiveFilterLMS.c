#include <stdio.h>
#include <stdlib.h>
void LMSfilter(float *u, float *d, int n, int m, float mu, float *ws, float **y, float **e) {
    *y = (float *)malloc(n * sizeof(float));
    *e = (float *)malloc(n * sizeof(float));
    float w[m];
    for (int i = 0; i < m; ++i) {
        w[i] = ws[i];
    }
    for (int i = 0; i < n; ++i) {
        (*y)[i] = 0.0;
        if (i < m) continue;
        for (int j = 0; j < m; ++j) {
            (*y)[i] += w[j] * u[i - j];
        }
        (*e)[i] = d[i] - (*y)[i];
        for (int j = 0; j < m; ++j) {
            w[j] += mu * (*e)[i] * u[i - j];
        }
    }
}

int main() {
    float *u, *d;
    int n;
    int m = 200000;
    float mu = 0.01;
    float ws[m];
    for (int i = 0; i < m; ++i) {
        ws[i] = 0.0;
    }
    readAudioFile("inputaudio",&u,&n); 
    readAudioFile("desiredsignalaudio",&d);
    float *y, *e;
   
    LMSfilter(u, d, n, m, mu, ws, &y, &e);
   
    writeAudioFile("removednoiceaudio",e,n); 

    free(u);
    free(d);
    free(y);
    free(e);
    return 0;
} 
