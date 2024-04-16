#Realizar la secuencia de referencias de páginas y contar el número de fallos de página suponiendo los algoritmos de reemplazo FIFO. que se solicite una lista de las direcciones logicas de las paginas y el tamaño de la memoria principal. que devuelva el numero de fallos de pagina.

def FIFO(page_references, memory_size):
    memory = []  # Lista para almacenar los marcos de página
    page_faults = 0  # Contador de fallos de página
    reference_sequence = []  # Lista para almacenar la secuencia de referencias de páginas
    page_fault_info = []  # Lista para almacenar los fallos de página de cada dirección de página
    
    for page in page_references:
        # Agregar la página actual a la secuencia de referencias
        reference_sequence.append(page)
        
        # Si la página no está en la memoria, se produce un fallo de página
        if page not in memory:
            page_faults += 1
            page_fault_info.append((page, True))  # Agregar el fallo de página a la lista de información
            # Si la memoria está llena, se elimina la página más antigua (primera en entrar)
            if len(memory) == memory_size:
                memory.pop(0)
            # Se carga la nueva página al final de la memoria (último en entrar)
            memory.append(page)
        else:
            page_fault_info.append((page, False))  # No hubo fallo de página para esta dirección de página
    
    return page_faults, reference_sequence, page_fault_info

# Función para solicitar una lista de direcciones lógicas de páginas y el tamaño de la memoria principal
def main():
    # Solicitar la lista de direcciones lógicas de las páginas
    page_references = list(map(int, input("Ingrese la lista de direcciones lógicas de las páginas separadas por espacios: ").split()))
    
    # Solicitar la secuencia de referencias de páginas
    reference_sequence = list(map(int, input("Ingrese la secuencia de referencias de páginas separadas por espacios: ").split()))
    
    memory_size = 4  # Tamaño de la memoria principal en marcos de página
    
    # Tomar las primeras 10 direcciones para identificar el offset y hacer el conteo de página hasta 6
    page_references = [page // 64 for page in page_references[:10]]
    
    # Llamada a la función FIFO para contar los fallos de página y obtener la secuencia de referencias de páginas
    faults, _, page_fault_info = FIFO(reference_sequence, memory_size)
    
    print("El número de fallos de página utilizando el algoritmo FIFO es:", faults)
    print("Los fallos de página de cada dirección de página son:", page_fault_info)

if __name__ == "__main__":
    main()





