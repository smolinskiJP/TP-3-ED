import random
import os
import names # Biblioteca para gerar nomes aleatórios. Instale com: pip install names

# --- PARÂMETROS GERAIS ---

EVENT_TYPES = ["AR", "RM", "UR", "TR", "EN"]
MAX_ARMAZEM_ID = 50
MAX_SECAO_ID = 10

# --- FUNÇÕES DE GERAÇÃO DE EVENTOS E CONSULTAS (sem alterações) ---

def gerar_eventos_pacote(id_pacote, remetente, destinatario, num_eventos_max):
    """Gera uma cadeia de eventos para um único pacote."""
    eventos = []
    timestamp = random.randint(1, 1000)
    armazem_orig = random.randint(0, MAX_ARMAZEM_ID)
    armazem_dest = random.randint(0, MAX_ARMAZEM_ID)
    while armazem_orig == armazem_dest:
        armazem_dest = random.randint(0, MAX_ARMAZEM_ID)
    
    eventos.append(f"{timestamp:07d} EV RG {id_pacote:03d} {remetente} {destinatario} {armazem_orig:03d} {armazem_dest:03d}")
    
    ultimo_timestamp = timestamp
    num_eventos = random.randint(1, num_eventos_max)
    for _ in range(num_eventos):
        ultimo_timestamp += random.randint(10, 500)
        tipo_evento = random.choice(EVENT_TYPES)
        
        if tipo_evento in ["AR", "RM", "UR"]:
            armazem = random.randint(0, MAX_ARMAZEM_ID)
            secao = random.randint(0, MAX_SECAO_ID)
            eventos.append(f"{ultimo_timestamp:07d} EV {tipo_evento} {id_pacote:03d} {armazem:03d} {secao:03d}")
        elif tipo_evento == "TR":
            orig = random.randint(0, MAX_ARMAZEM_ID)
            dest = random.randint(0, MAX_ARMAZEM_ID)
            while orig == dest:
                dest = random.randint(0, MAX_ARMAZEM_ID)
            eventos.append(f"{ultimo_timestamp:07d} EV {tipo_evento} {id_pacote:03d} {orig:03d} {dest:03d}")
        elif tipo_evento == "EN":
            armazem = random.randint(0, MAX_ARMAZEM_ID)
            eventos.append(f"{ultimo_timestamp:07d} EV {tipo_evento} {id_pacote:03d} {armazem:03d}")
            break 
            
    return eventos, ultimo_timestamp

def gerar_consultas(num_consultas, max_timestamp, pacotes_existentes, clientes_existentes):
    """Gera uma lista de consultas aleatórias."""
    consultas = []
    for _ in range(num_consultas):
        timestamp = random.randint(1, max_timestamp)
        
        if random.random() < 0.5 and pacotes_existentes:
            id_pacote = random.choice(pacotes_existentes)
            consultas.append(f"{timestamp:07d} PC {id_pacote:03d}")
        elif clientes_existentes:
            cliente = random.choice(clientes_existentes)
            consultas.append(f"{timestamp:07d} CL {cliente}")
            
    return consultas

def criar_arquivo_entrada(path, params):
    """Cria um arquivo de entrada completo com base nos parâmetros."""
    clientes = [names.get_first_name().upper() for _ in range(params['num_clientes'])]
    if not clientes: clientes = ["CLIENTE_UNICO"] # Garante que haja pelo menos um cliente
    
    pacotes_ids = list(range(1, params['num_pacotes'] + 1))
    
    todas_as_linhas = []
    max_timestamp = 0
    
    for id_pac in pacotes_ids:
        remetente = random.choice(clientes)
        destinatario = random.choice(clientes)
        while remetente == destinatario:
            destinatario = random.choice(clientes)
            
        eventos_pacote, ultimo_ts = gerar_eventos_pacote(id_pac, remetente, destinatario, params['eventos_por_pacote'])
        todas_as_linhas.extend(eventos_pacote)
        
        if ultimo_ts > max_timestamp:
            max_timestamp = ultimo_ts
            
    consultas = gerar_consultas(params['num_consultas'], max_timestamp + 500, pacotes_ids, clientes)
    todas_as_linhas.extend(consultas)
    todas_as_linhas.sort()
    
    with open(path, 'w', encoding='utf-8') as f:
        for linha in todas_as_linhas:
            f.write(linha + "\n")

# --- FUNÇÕES DE GERAÇÃO DE CENÁRIOS DE TESTE ---

def gerar_cenarios_variando_clientes(base_path, num_arquivos=100):
    """Gera cenários variando continuamente o número de clientes."""
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    print(f"Gerando {num_arquivos} cenários variando clientes em '{base_path}'...")

    params_base = {
        'num_pacotes': 1000,
        'eventos_por_pacote': 10,
        'num_consultas': 500
    }

    for i in range(num_arquivos):
        params = params_base.copy()
        params['num_clientes'] = random.randint(10, 500)
        nome_arquivo = f"clientes_{i+1:03d}_C{params['num_clientes']}.txt"
        criar_arquivo_entrada(os.path.join(base_path, nome_arquivo), params)

def gerar_cenarios_variando_pacotes(base_path, num_arquivos=100):
    """Gera cenários variando continuamente o número de pacotes."""
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    print(f"Gerando {num_arquivos} cenários variando pacotes em '{base_path}'...")
    
    params_base = {
        'num_clientes': 100,
        'eventos_por_pacote': 10,
        'num_consultas': 500
    }
    
    for i in range(num_arquivos):
        params = params_base.copy()
        params['num_pacotes'] = random.randint(100, 5000)
        nome_arquivo = f"pacotes_{i+1:03d}_P{params['num_pacotes']}.txt"
        criar_arquivo_entrada(os.path.join(base_path, nome_arquivo), params)
        
def gerar_cenarios_variando_consultas(base_path, num_arquivos=100):
    """Gera cenários variando continuamente o número de consultas."""
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    print(f"Gerando {num_arquivos} cenários variando consultas em '{base_path}'...")

    params_base = {
        'num_pacotes': 1000,
        'num_clientes': 100,
        'eventos_por_pacote': 10
    }

    for i in range(num_arquivos):
        params = params_base.copy()
        params['num_consultas'] = random.randint(100, 5000)
        nome_arquivo = f"consultas_{i+1:03d}_Q{params['num_consultas']}.txt"
        criar_arquivo_entrada(os.path.join(base_path, nome_arquivo), params)

# NOVO: Função para gerar cenários variando o número de eventos por pacote
def gerar_cenarios_variando_eventos(base_path, num_arquivos=100):
    """Gera cenários variando continuamente o número de eventos por pacote."""
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    print(f"Gerando {num_arquivos} cenários variando eventos por pacote em '{base_path}'...")

    # Parâmetros base (fixos)
    params_base = {
        'num_pacotes': 500,
        'num_clientes': 100,
        'num_consultas': 200
    }

    for i in range(num_arquivos):
        params = params_base.copy()
        # Varia o número de eventos por pacote continuamente
        params['eventos_por_pacote'] = random.randint(5, 500)
        
        nome_arquivo = f"eventos_{i+1:03d}_E{params['eventos_por_pacote']}.txt"
        criar_arquivo_entrada(os.path.join(base_path, nome_arquivo), params)

# --- EXECUÇÃO PRINCIPAL ---

if __name__ == "__main__":
    random.seed(42) # Para resultados reproduzíveis
    base_dir = "entradas_geradas_tp3"
    
    # Gera 200 arquivos de teste para cada cenário
    gerar_cenarios_variando_clientes(os.path.join(base_dir, "variando_clientes"), num_arquivos=200)
    gerar_cenarios_variando_pacotes(os.path.join(base_dir, "variando_pacotes"), num_arquivos=200)
    gerar_cenarios_variando_consultas(os.path.join(base_dir, "variando_consultas"), num_arquivos=200)
    gerar_cenarios_variando_eventos(os.path.join(base_dir, "variando_eventos"), num_arquivos=200)
    
    print(f"\nArquivos de entrada gerados com sucesso no diretório '{base_dir}'!")
