import serial
import datetime

# ajuste a porta serial do seu sistema
PORTA_SERIAL = 'COM5'
BAUD_RATE = 9600
ARQUIVO_LOG = 'log_acessos.txt'

def grava_log(uid, status):
    agora = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    linha = f"{agora} - UID: {uid} - {status}\n"
    with open(ARQUIVO_LOG, 'a') as f:
        f.write(linha)
    print(linha, end='')

def main():
    arduino = serial.Serial(PORTA_SERIAL, BAUD_RATE, timeout=1)
    uid_atual = None

    try:
        while True:
            linha = arduino.readline().decode('utf-8').strip()
            if not linha:
                continue

            print("Arduino:", linha)

            if linha.startswith("UID detectado:"):
                # Captura o UID
                uid_atual = linha.replace("UID detectado: ", "").strip()
            elif linha == "Cartão autorizado!":
                if uid_atual:
                    grava_log(uid_atual, "ACESSO PERMITIDO")
                    uid_atual = None
            elif linha == "Cartão não autorizado.":
                if uid_atual:
                    grava_log(uid_atual, "ACESSO NEGADO")
                    uid_atual = None

    except KeyboardInterrupt:
        print("Encerrando...")
    finally:
        arduino.close()

if _name_ == "_main_":
    main()