🌟 Visão Geral
O objetivo principal é criar uma "porta inteligente" que abre somente para cartões RFID autorizados. Todas as interações são registradas, e um software em Python permite visualizar o status do acesso e um histórico detalhado.

✨ Funcionalidades
Leitura de Cartões RFID: Identifica cartões RFID (Mifare RC522).

Controle de Acesso: Verifica se o UID (Unique Identifier) do cartão lido está autorizado.

Acionamento de Servo Motor: Simula a abertura e fechamento de uma porta após um acesso autorizado.

Feedback Visual: Um LED indica o status (acesso permitido/negado).

Comunicação Serial: O Arduino envia dados de status e UID do cartão para o computador via porta serial.

Interface Gráfica (Python): Exibe o status "ACESSO PERMITIDO!" ou "ACESSO NEGADO!" em tempo real.

Sistema de Log: Registra cada tentativa de acesso (UID do cartão, status e timestamp) em um arquivo de texto para auditoria.

🛠 Tecnologias Utilizadas
Hardware
Arduino Uno: Microcontrolador principal.

Módulo Leitor RFID RC522: Para leitura dos cartões.

Servo Motor (SG90 ou similar): Para simular a abertura da porta.

LED: Indicador visual de acesso.

Jumpers e Protoboard: Para conexões.

Software
Arduino IDE: Para programar o Arduino.

Bibliotecas Arduino: SPI.h, MFRC522.h, Servo.h.

Python 3.x: Linguagem de programação para a interface e o log.

Bibliotecas Python: pyserial, tkinter (para GUI), datetime, threading.

⚙️ Requisitos
Hardware:

Placa Arduino Uno.

Módulo Leitor RFID RC522 + Cartões RFID/Tags.

Servo Motor.

LED e um resistor de 220 ohms (para o LED).

Fios jumpers (macho-macho, macho-fêmea).

Protoboard.

Cabo USB para Arduino.

Software:

Arduino IDE instalado.

Python 3.x instalado.

Acesso à internet para download de bibliotecas.

🚀 Instalação e Configuração
1. Configuração do Hardware (Arduino)
Conecte os componentes ao seu Arduino Uno conforme o diagrama abaixo e as definições de pinos no código:

Módulo RFID RC522:

SDA (SS) ➡️ Arduino Digital 10

SCK ➡️ Arduino Digital 13

MOSI ➡️ Arduino Digital 11

MISO ➡️ Arduino Digital 12

RST ➡️ Arduino Digital 9

VCC ➡️ Arduino 3.3V

GND ➡️ Arduino GND

LED:

Perna Longa (Ânodo) ➡️ Resistor (220 ohm) ➡️ Arduino Digital 5

Perna Curta (Cátodo) ➡️ Arduino GND

Servo Motor:

Fio Laranja/Amarelo (Sinal) ➡️ Arduino Digital 2

Fio Vermelho (VCC) ➡️ Arduino 5V

Fio Marrom/Preto (GND) ➡️ Arduino GND



projecthub.arduino.cc
2. Configuração do Software (Arduino IDE)
Abra o Arduino IDE.

Instale as bibliotecas:

Vá em Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...

Busque e instale MFRC522 (geralmente por "MFRC522 by Miguel Balboa").

Busque e instale Servo (já deve estar instalada por padrão, mas verifique).

Copie o código do arquivo arduino_rfid_code.ino (ou o código que foi fornecido a você) para o Arduino IDE.

Ajuste o UID Autorizado: No código Arduino, localize a linha byte authorizedUID[] = {0xFF, 0x1F, 0xC0, 0xC4};. Substitua este UID pelo UID do seu próprio cartão RFID que deseja autorizar. Você pode descobrir o UID do seu cartão lendo-o com o código e observando a saída no Monitor Serial antes de configurar.

Compile e Carregue:

Selecione a placa Tools > Board > Arduino AVR Boards > Arduino Uno.

Selecione a porta Tools > Port > (A porta do seu Arduino, ex: COM3, /dev/ttyUSB0).

Clique em Upload (seta para a direita).

3. Configuração do Software (Python)
Instale a biblioteca pyserial:

Abra o terminal ou Prompt de Comando.

Execute: pip install pyserial

Salve o script Python: Copie o código do arquivo rfid_monitor.py (ou o código que foi fornecido a você) e salve-o em um arquivo .py (ex: rfid_monitor.py) em seu computador.

Ajuste a Porta Serial no Python:

Abra o arquivo rfid_monitor.py.

Localize a linha SERIAL_PORT = 'COM3' (ou similar).

Mude 'COM3' para a porta serial correta do seu Arduino (a mesma que você usou no Arduino IDE).

🚀 Como Usar
Certifique-se de que o código Arduino está carregado na sua placa e que ela está conectada ao computador via USB.

Abra o terminal ou Prompt de Comando e navegue até a pasta onde você salvou o arquivo rfid_monitor.py.

Execute o script Python:

python rfid_monitor.py

Uma janela de interface gráfica (GUI) será aberta. Ela tentará se conectar automaticamente ao Arduino.

Aproxime um cartão RFID do leitor:

Se for um cartão autorizado: O LED verde acenderá, o servo se moverá (abrindo a "porta") e a GUI mostrará "ACESSO PERMITIDO!".

Se for um cartão não autorizado: A GUI mostrará "ACESSO NEGADO!".

Verifique o Log: O arquivo log_acessos.txt será criado ou atualizado na mesma pasta do script Python, registrando cada evento de acesso com detalhes.

📂 Estrutura do Projeto
.
├── arduino_rfid_code.ino    # Código fonte para o Arduino
├── rfid_monitor.py          # Script Python para GUI e log
├── log_acessos.txt          # Arquivo de log gerado pelo script Python
└── README.md                # Este arquivo

💡 Próximos Passos e Melhorias Futuras
Adicionar Banco de Dados: Substituir o arquivo de log simples por um banco de dados (ex: SQLite) para um gerenciamento mais robusto dos registros.

Interface Web: Desenvolver uma interface web (com Flask ou Django) para monitoramento e controle remoto.

Notificações: Enviar notificações (e-mail, Telegram, etc.) em caso de tentativas de acesso negadas.

Gerenciamento de Usuários: Criar um sistema para adicionar/remover UIDs autorizados dinamicamente via interface.

Sensor de Porta: Integrar um sensor magnético para saber se a porta está realmente aberta ou fechada.

Sinal Sonoro: Adicionar um buzzer para indicar acesso permitido/negado.

Segurança: Implementar criptografia mais robusta na comunicação ou validação de UIDs.
