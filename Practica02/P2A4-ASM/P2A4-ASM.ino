void setup()
{
DDRB = DDRB | B10000000; // Data Direction Register B: Inputs 0-6, Output 7
}
void loop()
{
asm (
"inicio: \n\t"
"sbi 0x05,0x07 \n\t" // empieza el escrito en el eeprom
"call tiempo \n\t" // llama a la variable de tiempo
"cbi 0x05,0x07 \n\t" // limpia bit en los registros de i/o 0x05 0x07
"call tiempo \n\t" // llama tiempo
"jmp main \n\t" // resetea el handler
"tiempo: \n\t" //
"LDI r22, 45 \n\t" //empieza el programa principal en el registro 22 ← 45
"LOOP_3: \n\t" 
"LDI r21, 255 \n\t" // empieza el programa principal en el registro 21 ← 255
"LOOP_2: \n\t" //
"LDI r20, 255 \n\t" //empieza el programa principal en el registro 20 ← 255 
"LOOP_1: \n\t" //
"DEC r20 \n\t" //decrementa registro 20
"BRNE LOOP_1 \n\t"
"DEC r21 \n\t" //decrementa registro 21
"BRNE LOOP_2 \n\t"
"DEC r22 \n\t" //decrementa registro 22
"BRNE LOOP_3 \n\t"
"ret \n\t" //termina el código 
);
}