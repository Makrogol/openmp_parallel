f = open('input_data/input.txt', 'r')
n, m = map(int, f.readline().split())
f.close()

f = open('input_data/current_count_threads.txt', 'r')
count_threads = int(f.readline().split()[0])
f.close()

time = {"Последовательное решение": 0.0,
        "Параллельное решение": 0.0,
        "Параллельное решение с reduction": 0.0,
        "Параллельное решение с sections": 0.0}

count = 0
f = open("input_data/variabels.txt", 'r')
for line in f.readlines():
    if line.find('COUNT_ITERATIONS') != -1:
        count = int(line.split('=')[-1])
        break
f.close()

f = open("out/intermediate_output.txt", 'r')
for _ in range(count):
    i = 0
    while i < len(time.keys()):
        line = f.readline().split()
        if len(line) > 0:
            time[list(time.keys())[i]] += float(line[0])
            i += 1
f.close()

f = open("out/output.txt", 'a')
f.write(f'{count_threads}\n')
f.write(f'{n} {m}\n')
for el in time.keys():
    time[el] /= count
    f.write('{:.6f}\n'.format(time[el]))
f.close()
