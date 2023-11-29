# Horta Hidropônica
## _Prova de conceito de automatização utilizando Arduino_

![Projeto de hidroponia](https://i.imgur.com/YprQ7QA.jpg)

Este projeto visa criar uma solução eficiente e automatizada para o cultivo de plantas em um ambiente hidropônico. A automação é realizada por meio de um Arduino, sensores e atuadores que monitoram e controlam diversos aspectos do ambiente de cultivo.

Além disso, o projeto conta com uma interface gráfica para realizar o monitoramento das condições da horta de forma simples e amigável:

![Imagem da interface gráfica](https://i.imgur.com/ITc2FAU.png)

## Funcionalidades

1. Monitoramento de Parâmetros Ambientais:
    * Sensor de luminosidade
    * Sensor de temperatura
2. Controle de Ambiente:
    * Sistema de iluminação baseado na luminosidade
    * Sistema de irrigação automática baseado na temperatura
3. Integração com Interface Gráfica:
    * Acompanhamento visual dos dados ambientais

## Pacotes utilizados

Essa aplicação foi criada utilizando os seguitnes pacotes:

| Pacote | Link |
| ------ | ------ |
| TKinter | https://docs.python.org/3/library/tkinter.html |
| PySerial | https://pypi.org/project/pyserial/ |
| Pillow | https://pypi.org/project/Pillow/ |

## Desenvolvimento futuro

Este projeto possui várias possibilidades de funcionalidades adicionais, que podem incluir:

- Mais sensores como de pH do solo ou qualidade da água
- Módulo de WiFi para habilitar controle e alertas remotos
- Coleta e armazenamento em banco de dados para análise