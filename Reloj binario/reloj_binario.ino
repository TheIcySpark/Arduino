const int pin_segundos = 8;
unsigned long tiempo, tiempo_anterior;
int segundos, minutos, horas;

void setup()
{
    tiempo_anterior = segundos = minutos = horas = 0;

    for(int i = 2; i <= 12 ; i++) pinMode(i, OUTPUT);
}

int * conversion_binario(int x, int ret[]){
    for(int i = 0; i < 8; i++){
        ret[i] = 0;
    }
    int i = 0;
    while(x >= 1){
        ret[i++] = x % 2;
        x /= 2;
    }
    return ret;
}

void mostrar_hora(){
    int a1[8];
    int a2[8];
    int* minutos_binario = conversion_binario(minutos, a1);
    int* horas_binario = conversion_binario(horas, a2);
    for(int i = 0; i < 6; i++){
        digitalWrite(i + 2, *(minutos_binario + i) );
    }
    for(int i = 0; i < 4; i++){
        digitalWrite(i + 9, *(horas_binario + i) );
    }
}

void calcular_hora(){
    tiempo = millis();
    if(abs(tiempo - tiempo_anterior) >= 1000){
        tiempo_anterior = tiempo;
        segundos ++;
        digitalWrite(pin_segundos, HIGH);
        if(segundos >= 60){
            segundos = 0;
            minutos ++;
            if(minutos >= 60){
                horas ++ ;
                minutos = 0;
                if(horas > 12) horas = 0;
            }
        }
        delay(500);
        digitalWrite(pin_segundos, LOW);
    }

}

void loop()
{
    calcular_hora();
    mostrar_hora();
}
