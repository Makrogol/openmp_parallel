f = open("main.cpp", 'r')
code = f.readlines()
f.close()
threads = int(open('input_data/current_count_threads.txt').readline())

for i in range(len(code)):
    if code[i].find('#define NTHREADS') != -1:
        code[i] = f'#define NTHREADS {threads}\n'

f = open("main.cpp", 'w')
f.write(''.join(code))
f.close()
