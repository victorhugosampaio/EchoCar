import os
import random
import shutil
import argparse


def select_random_samples(source_folder, destination_folder, sample_size=1500):
    # Garante que a pasta de destino existe
    os.makedirs(destination_folder, exist_ok=True)

    # Lista todos os arquivos .wav na pasta de origem
    wav_files = [f for f in os.listdir(source_folder) if f.endswith(".wav")]

    # Verifica se há arquivos suficientes
    if len(wav_files) < sample_size:
        raise ValueError("A quantidade de arquivos .wav na pasta é menor que o número solicitado.")

    # Seleciona aleatoriamente os arquivos
    selected_files = random.sample(wav_files, sample_size)

    # Copia os arquivos selecionados para a pasta de destino
    for file in selected_files:
        shutil.copy(os.path.join(source_folder, file), os.path.join(destination_folder, file))

    print(f"{sample_size} arquivos foram copiados para {destination_folder}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Seleciona aleatoriamente 1500 arquivos .wav de uma pasta.")
    parser.add_argument("source_folder", type=str, help="Caminho para a pasta de origem contendo arquivos .wav")
    parser.add_argument("destination_folder", type=str,
                        help="Caminho para a pasta de destino onde os arquivos serão copiados")
    args = parser.parse_args()

    select_random_samples(args.source_folder, args.destination_folder)
