# Sensores Lego EV3: nova possibilidade de uso 

## Resumo 

## Motivação

## O processo

Inicialmente, em busca de informações técnicas sobre os sensores e sobre toda a coleção LEGO MINDSTORM EV3, encontrei ampla documentação (nomeada Developer Kit) fornecida pela própria LEGO, que versa sobre *Firwmare, Hardware e Comunicação*, podendo ser acessada [neste link](https://education.lego.com/en-us/product-resources/mindstorms-ev3/downloads/developer-kits). As informações mais relevantes para a execução do projeto encontram-se na seção *Hardware*, a qual mantive anexada ao repositório.

No intuito de estabelecer conexão física com os sensores, para assim compreender a comunicação entre eles e o *brick* e mais tarde realizá-la sem o *brick*, foi preciso a construção de uma placa adaptadora, a qual contou com o conector específico da coleção EV3: 6 wire RJ-12 right side.

Com a placa montada, o mapeamento dos pinos dela foi realizado seguindo os esquemáticos dos sensores — visando identificar pinos como GND, VCC e UART TX/RX. Com isso, foi possível conectar os sensores ao analisador lógico USB, semelhante a esse do [link](https://www.usinainfo.com.br/testadores-e-medidores-diversos/analisador-logico-24mhz-8ch-al24-2691.html), permitindo conhecer/analisar os pacotes de dados enviados por eles. Tais pacotes foram interpretados com o auxílio do *software* [Logic 2](https://www.saleae.com/downloads/) (da Saleae), da documentação oficial da LEGO e da documentação do projeto LeJOS, o qual conduziu uma análise do [Protocolo dos Sensores UART](https://sourceforge.net/p/lejos/wiki/UART%20Sensor%20Protocol/). Maiores detalhes sobre a comunicação UART, capturas do analisador lógico e a interpretação dos pacotes encontram-se na devida pasta.