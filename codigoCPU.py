import subprocess
import matplotlib.pyplot as plt

# Função para coletar dados do escalonamento com trace-cmd
def coletar_dados_trace_cmd():
    print("Coletando dados de escalonamento com 'trace-cmd'...")
    # Executa o trace-cmd para capturar eventos de escalonamento
    subprocess.run(['sudo', 'trace-cmd', 'record', '-e', 'sched_switch', '-e', 'sched_wakeup', 'sleep', '10'])
    
    # Converte o arquivo trace.dat para um arquivo de texto
    with open('trace_output.txt', 'w') as f:
        subprocess.run(['sudo', 'trace-cmd', 'report'], stdout=f)
    
    print("Dados coletados e armazenados em 'trace_output.txt'.")

# Função para analisar o arquivo txt gerado pelo trace-cmd
def analisar_log_trace_cmd():
    print("Analisando o arquivo de log do trace-cmd...")
    eventos_por_cpu = {}

    # Abre o arquivo de log gerado pelo trace-cmd report
    with open('trace_output.txt', 'r') as f:
        for linha in f:
            # Limite de diagnóstico para imprimir algumas linhas no terminal
            print(f"Analisando linha: {linha.strip()}")

            # Procura por eventos sched_switch
            if "sched_switch" in linha:
                partes = linha.split()
                try:
                    # O tempo de início está na terceira posição, ex: '1520.318590:'
                    tempo_inicio = float(partes[2].replace(":", ""))  # Remove o ':' e converte para float

                    # O número da CPU está na quarta posição, ex: '[002]'
                    cpu = int(partes[1].replace('[', '').replace(']', ''))

                    # O nome dos processos está antes e depois do '==>'
                    processo_1 = partes[4].split(':')[0]  # Nome do processo anterior (antes do ':')
                    processo_2 = partes[8].split(':')[0]  # Nome do próximo processo (antes do ':')

                    # Inicializa a lista para a CPU se necessário
                    if cpu not in eventos_por_cpu:
                        eventos_por_cpu[cpu] = []

                    # Adiciona o tempo e os processos ao array da CPU correspondente
                    eventos_por_cpu[cpu].append((tempo_inicio, processo_1, processo_2))

                except (ValueError, IndexError) as e:
                    print(f"Erro ao processar a linha: {e}")
                    continue

    # Mostra o total de eventos por CPU
    for cpu, eventos in eventos_por_cpu.items():
        print(f"Total de {len(eventos)} eventos analisados na CPU {cpu}.")

    return eventos_por_cpu

# Função para gerar gráficos com os tempos coletados, separados por CPU
def gerar_graficos_trace_cmd(eventos_por_cpu):
    print("Gerando gráficos...")

    # Itera sobre cada CPU e gera um gráfico para os eventos dela
    for cpu, eventos in eventos_por_cpu.items():
        tempos_inicio = [evento[0] for evento in eventos]  # Tempo de início dos eventos
        processos = [evento[1] for evento in eventos]      # Nome do processo anterior

        # Cria o gráfico para a CPU atual
        plt.figure(figsize=(10, 6))
        plt.plot(tempos_inicio, label=f"CPU {cpu}", color='blue', marker='x')

        plt.title(f"Tempos de Escalonamento de Processos na CPU {cpu}")
        plt.xlabel("Tempo (ms)")
        plt.ylabel("Índice do Evento")
        plt.legend()
        plt.grid(True)
        plt.show()

# Função principal para coordenar o monitoramento
def main():
    # Coletar os dados de escalonamento
    coletar_dados_trace_cmd()

    # Analisar o arquivo de log gerado
    eventos_por_cpu = analisar_log_trace_cmd()

    # Gerar gráficos com base nos dados analisados, separados por CPU
    if eventos_por_cpu:
        gerar_graficos_trace_cmd(eventos_por_cpu)
    else:
        print("Nenhum dado de escalonamento encontrado para gerar gráficos.")

# Execução do programa
if __name__ == "__main__":
    main()
