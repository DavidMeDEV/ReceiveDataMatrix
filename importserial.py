import serial

porta_serial = 'COM8' 
baud_rate = 9600  

serial_port = serial.Serial(porta_serial, baud_rate, timeout=1)

nome_arquivo = 'todas_matrizes.csv'
while True:
    linha = serial_port.readline().decode().strip()
    if linha=='inicio':
        with open(nome_arquivo, 'w') as arquivo:
            while linha!='fim':
                linha = serial_port.readline().decode().strip()
                arquivo.write(linha + '\n')
                print('salvando dados')
        print("fim do registro de arquivos")
        break
    else:
        print('impossível salvar algo')