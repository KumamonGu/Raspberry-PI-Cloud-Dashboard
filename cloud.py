#!/usr/bin/python3
import time
import datetime
import subprocess
import sys
import psutil
import random
import math

# 检查命令行参数
if len(sys.argv) < 4:
    print("Usage: democloud.py <InfluxDB_IP_Address> <username> <password>")
    sys.exit(1)

# 配置
f_sampling = 1
timestamp = datetime.datetime.now().timestamp()

def simulate_data(base, amplitude, frequency, noise_level, timestamp):
    noise = random.uniform(-noise_level, noise_level)
    return base + amplitude * math.sin(2 * math.pi * frequency * timestamp) + noise

while True:
    for i in range(f_sampling):
        timestamp += 1 / f_sampling
        
        # 收集系统数据
        cpu = psutil.cpu_percent(interval=1)
        mem = psutil.virtual_memory()
        disk = psutil.disk_usage('/')
        load = psutil.getloadavg()
        temperature = psutil.sensors_temperatures().get('cpu_thermal', [])[0].current if psutil.sensors_temperatures() else None

        # 模拟其他传感器数据
        room_temperature = simulate_data(22, 2, 0.001, 0.5, timestamp)
        humidity = simulate_data(50, 10, 0.001, 2, timestamp)
        air_quality = simulate_data(100, 20, 0.001, 5, timestamp)
        co_percent = simulate_data(0.04, 0.01, 0.001, 0.002, timestamp)

        # 组织数据成 InfluxDB 格式
        data = (
            f"demo,location=UGA "
            f"cpu_usage={cpu},mem_percent={mem.percent},"
            f"disk_used={disk.used},disk_free={disk.free},disk_percent={disk.percent},"
            f"load_1={load[0]},load_5={load[1]},load_15={load[2]},"
            f"temperature={temperature},room_temperature={room_temperature},"
            f"humidity={humidity},air_quality={air_quality},co_percent={co_percent} "
            f"{int(timestamp * 10e8)}"
        )
        
        # 使用 curl 发送数据
        http_post = f"curl -i -XPOST 'http://{sys.argv[1]}:8086/write?db=test' -u {sys.argv[2]}:{sys.argv[3]} --data-binary '{data}'"
        subprocess.call(http_post, shell=True)

        time.sleep(1 / f_sampling)

