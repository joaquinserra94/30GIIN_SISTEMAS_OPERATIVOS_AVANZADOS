from collections import deque
from tabulate import tabulate

def LRU(page_references, memory_size):
    memory = deque(maxlen=memory_size)  # Cola para almacenar los marcos de página
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
            
            if len(memory) == memory_size:  # Si la memoria está llena, se elimina la página menos recientemente usada
                memory.popleft()
            
            memory.append(page)  # Se carga la nueva página al final de la memoria
        else:
            page_fault_info.append((page, False))  # No hubo fallo de página para esta dirección de página
            memory.remove(page)  # Mover la página al final de la cola para indicar que ha sido usada recientemente
            memory.append(page)
    
    return page_faults, reference_sequence, page_fault_info

def main():
    # Solicitar la lista de direcciones lógicas de las páginas
    page_references = list(map(int, input("Ingrese la lista de direcciones lógicas de las páginas separadas por espacios: ").split()))
    
    # Solicitar la secuencia de referencias de páginas
    reference_sequence = list(map(int, input("Ingrese la secuencia de referencias de páginas separadas por espacios: ").split()))
    
    memory_size = 4  # Tamaño de la memoria principal en marcos de página
    
    # Llamada a la función LRU para contar los fallos de página y obtener la secuencia de referencias de páginas
    faults, _, page_fault_info = LRU(reference_sequence, memory_size)
    
    # Crear la tabla con los datos de los marcos de página para cada dirección lógica
    table = tabulate(page_fault_info, headers=["Dirección Lógica", "Fallo de Página"], tablefmt="pipe")
    
    # Mostrar la tabla
    print(table)
    print(f"Total de fallos de página: {faults}")

if __name__ == "__main__":
    main()
