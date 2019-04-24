Compilar:

g++ algorithms.cpp operators.cpp roll_block.cpp -Ofast -o roll_block

Executar:

roll_block <level.txt>

Níveis têm de estar na pasta levels

Exemplos:

roll_block 1
roll_block 2.txt
roll_block aries/1
roll_block taurus/2.txt

Usar:

Escolher opção: 
1 - Jogar: Utilizar WASD ou setas para mover o bloco

Legenda do mapa:

| -> Posição do bloco (em pé)
-- -> Posição do bloco (sentado)
_ -> Posição final
g -> Chão
  -> Vazio
C -> Botão (deitado)
X -> Botão (em pé)
c -> Chão expandido quando botão C ativo
x -> Chão expandido quando botão X ativo

Outra opções -> Resolver o nível utilizando algoritmo selecionado