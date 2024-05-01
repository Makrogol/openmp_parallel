import pandas as pd

max_count_threads = 0
f = open('input_data/variabels.txt', 'r')
for line in f.readlines():
    if line.find('MAX_COUNT_THREADS') != -1:
        max_count_threads = int(line.split('=')[-1])
        break
f.close()

f = open('input_data/sizes.txt', 'r')
sizes = [line.strip() for line in f.readlines()]
f.close()

f = open('out/output.txt', 'r')
lines = f.readlines()
for i in range(len(lines)):
    lines[i] = lines[i].strip()

count_threads_str = 'Размеры входных данных'
threads_num = [str(i) for i in range(1, max_count_threads + 1)]
solution_types_str = ['Последовательное решение', 
                      'Параллельное решение',
                      'Параллельное решение с reduction', 
                      'Параллельное решение с section']

list_table = {thread_num: [] for thread_num in threads_num}
i = 0
while i < len(lines):
    if len(lines[i]) > 0:
        thread_num = lines[i]
        size = lines[i + 1]
        solution_types = list(map(float, lines[i + 2: i + 6]))
        list_table[thread_num] += solution_types
        i += 6
    else:
        i += 1
f.close()



multi_col_typle = []
for size in sizes:
    for solution_type in solution_types_str:
        multi_col_typle.append((count_threads_str, size, solution_type))

multiCol = pd.MultiIndex.from_tuples(multi_col_typle)
table = pd.DataFrame(index=threads_num, columns=multiCol)
for thread_num in threads_num:
    table.loc[thread_num] = list_table[thread_num]
table.to_excel('out/results.xlsx')
