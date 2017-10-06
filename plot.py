import sys

from matplotlib import pyplot as plt


def main():
    len_data = []
    time_data = []
    for line in sys.stdin:
        length, time = line.split(' ')
        len_data.append(length)
        time_data.append(time)

    plot(len_data, time_data)


def plot(x, y):
    plt.plot(x, y)
    plt.show()


if __name__ == '__main__':
    main()
