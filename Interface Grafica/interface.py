import serial #Biblioteca que interage com as portas do arduino
import tkinter as tk #Biblioteca de interface gráfica
import os
from PIL import Image, ImageTk #Biblioteca de manipulação de imagem

def atualizar_dados():
    #Pegar as informações de output e dividir em cada parte que interessa
    data = ser.readline().decode('utf-8').strip()
    partes = data.split('|')
    
    #Loop em cada parte do output
    for parte in partes:
        label, value = parte.split(':')
        #Se o label começa com L, trata-se de informação de luz
        if label == 'L':
            light_value = int(value)
            light_label.config(text=f"Nível de luz: {light_value}")
            
            #Mudamos a imagem dependendo do nível de luz
            if light_value > 150:
                light_icon.config(image=imagem_nivel_luz_alto)
            else:
                light_icon.config(image=imagem_nivel_luz_normal)

        #Se o label começa com T, trata-se de informação de temperatura        
        if label == 'T':
            temp_label.config(text=f"Temperatura: {value} °C")
            temp_icon.config(image=imagem_temperatura_normal)
        #Se o label começa com D4, trata-se de informação do pino digital 4 
        if label == 'D4':
            dp_value = int(value)

            #Mudamos a imagem dependendo se o pino está ligado (1) ou não (0)
            if dp_value > 0:
                temp_icon.config(image=imagem_temperatura_alta)
            else:
                temp_icon.config(image=imagem_temperatura_normal)

    root.after(1000, atualizar_dados)  #Agendar a próxima atualização em 1000 millisegundos

#Raiz da interface gráfica
root = tk.Tk()
#Título da janela
root.title("Dados dos Sensores Arduino")

#Carregar os ícones
resources_path = os.path.join(os.path.dirname(__file__), "resources")

nivel_luz_normal = Image.open(os.path.join(resources_path, "img6.png")).resize((250, 250))
nivel_luz_alto = Image.open(os.path.join(resources_path, "img3.png")).resize((250, 250))
temperatura_normal = Image.open(os.path.join(resources_path, "img1.png")).resize((250, 250))
temperatura_alta = Image.open(os.path.join(resources_path, "img5.png")).resize((250, 250))


imagem_nivel_luz_normal = ImageTk.PhotoImage(nivel_luz_normal)
imagem_nivel_luz_alto = ImageTk.PhotoImage(nivel_luz_alto)
imagem_temperatura_normal = ImageTk.PhotoImage(temperatura_normal)
imagem_temperatura_alta = ImageTk.PhotoImage(temperatura_alta)

#Nivel de luz
light_icon = tk.Label(root, image=imagem_nivel_luz_normal)
light_icon.pack(pady=10)
light_label = tk.Label(root, text="Nível de luz: ", font=("Helvetica", 34))
light_label.pack(pady=10)

#Temperatura
temp_icon = tk.Label(root, image=imagem_temperatura_normal)
temp_icon.pack(pady=10)
temp_label = tk.Label(root, text="Temperatura: ", font=("Helvetica", 34))
temp_label.pack(pady=10)

#Portal serial do Arduino
ser = serial.Serial('COM6', 9600)

#Iniciar os updates automaticos
root.after(0, atualizar_dados)

#Iniciar a interface
root.mainloop()
