import subprocess
import os
import csv
import time
import re

# --- Configurações ---

# Nome do seu programa C++ compilado
# Certifique-se de que ele esteja na pasta ./bin/
EXECUTABLE_PATH = "./bin/tp3.out"

# Diretório base onde as pastas com os cenários de teste foram geradas
BASE_INPUT_DIR = "entradas_geradas_tp3"

# Diretório onde os arquivos CSV com os resultados serão salvos
RESULTS_DIR = "data"


def extract_param_from_filename(filename, param_char):
    """
    Extrai um número do nome do arquivo com base em um caractere de parâmetro.
    Exemplo: para "clientes_001_C123.txt" e param_char='C', retorna 123.
    """
    # A expressão regular procura pelo caractere do parâmetro seguido por um ou mais dígitos
    match = re.search(f"{param_char}(\d+)", filename)
    if match:
        return int(match.group(1))
    return None

def run_single_scenario(executable, input_file):
    """
    Executa um único cenário e retorna o tempo de execução em segundos.
    """
    command = [executable, input_file]
    
    start_time = time.time()
    try:
        # Executa o comando, redirecionando a saída para DEVNULL para não poluir o terminal
        subprocess.run(
            command, 
            check=True, 
            stdout=subprocess.DEVNULL, 
            stderr=subprocess.PIPE
        )
    except subprocess.CalledProcessError as e:
        print(f"\nERRO ao executar '{input_file}':")
        print(f"O programa C++ retornou um erro:\n{e.stderr.decode('utf-8')}")
        return None # Retorna None em caso de erro

    end_time = time.time()
    
    return end_time - start_time

def process_scenario_folder(scenario_path, param_char, csv_filename, csv_header):
    """
    Processa todos os arquivos de uma pasta de cenário, executa os testes e salva os resultados.
    """
    if not os.path.isdir(scenario_path):
        print(f"Aviso: Diretório de cenário '{scenario_path}' não encontrado. Pulando.")
        return

    # Cria o arquivo CSV e escreve o cabeçalho
    with open(csv_filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(csv_header)

    # Lista todos os arquivos de entrada no diretório
    input_files = sorted([f for f in os.listdir(scenario_path) if f.endswith('.txt')])
    total_files = len(input_files)
    
    print(f"\n--- Processando {total_files} cenários de '{os.path.basename(scenario_path)}' ---")

    for i, filename in enumerate(input_files):
        input_filepath = os.path.join(scenario_path, filename)
        
        # Extrai o parâmetro relevante do nome do arquivo
        param_value = extract_param_from_filename(filename, param_char)
        if param_value is None:
            print(f"Aviso: Não foi possível extrair o parâmetro de '{filename}'. Pulando.")
            continue
            
        # Executa o teste e mede o tempo
        execution_time = run_single_scenario(EXECUTABLE_PATH, input_filepath)
        
        if execution_time is not None:
            # Salva o resultado no CSV imediatamente
            with open(csv_filename, 'a', newline='') as f:
                writer = csv.writer(f)
                writer.writerow([param_value, execution_time])
        
        # Imprime o progresso
        print(f"  Progresso: {i + 1}/{total_files} concluído.", end='\r')
    
    print(f"\nResultados salvos em '{csv_filename}'")


if __name__ == "__main__":
    # --- Verificações Iniciais ---
    if not os.path.exists(EXECUTABLE_PATH):
        print(f"ERRO: Executável '{EXECUTABLE_PATH}' não encontrado.")
        print("Certifique-se de que o projeto foi compilado com 'make all'.")
        exit(1)

    if not os.path.exists(BASE_INPUT_DIR):
        print(f"ERRO: Diretório de entradas '{BASE_INPUT_DIR}' não encontrado.")
        print("Execute o gerador de entradas primeiro.")
        exit(1)

    # Cria o diretório de resultados se ele não existir
    os.makedirs(RESULTS_DIR, exist_ok=True)

    # --- Execução dos Experimentos ---
    
    # Experimento 1: Variando Clientes
    process_scenario_folder(
        scenario_path=os.path.join(BASE_INPUT_DIR, "variando_clientes"),
        param_char='C',
        csv_filename=os.path.join(RESULTS_DIR, "resultados_clientes.csv"),
        csv_header=["num_clientes", "tempo_execucao_s"]
    )

    # Experimento 2: Variando Pacotes
    process_scenario_folder(
        scenario_path=os.path.join(BASE_INPUT_DIR, "variando_pacotes"),
        param_char='P',
        csv_filename=os.path.join(RESULTS_DIR, "resultados_pacotes.csv"),
        csv_header=["num_pacotes", "tempo_execucao_s"]
    )

    # Experimento 3: Variando Consultas
    process_scenario_folder(
        scenario_path=os.path.join(BASE_INPUT_DIR, "variando_consultas"),
        param_char='Q',
        csv_filename=os.path.join(RESULTS_DIR, "resultados_consultas.csv"),
        csv_header=["num_consultas", "tempo_execucao_s"]
    )

    print("\n--- Todos os experimentos foram concluídos! ---")
