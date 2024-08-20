# Raspberry-PI-Cloud-Dashboard
A Grafana Dashboard can be deployed on any Debian/Ubuntu machine(including Cloud VM or local machine) to monitor the system parameters of real-world Raspberry PIs. It can also be utilized to monitor sensor data if such sensors are connected to real-world Raspberry PIs.

## Tools
### For Dashboards that can be viewed on a Cloud VM 
Raspberry PI 5, InfluxDB, Grafana, Google Cloud VM
### For Dashboards that can be viewed on a Local Linux Machine 
Raspberry PI 5, InfluxDB, Grafana, Local Debian/Ubuntu Linux machine

## Step 1: Set up Raspberry PI and Sensors(if applicable)
Before You can really start, you need first to set up your Raspberry PIs. If your RPI comes with a pre-installed system(e.g. You bought it from companies like Canakit), please follow the instructions that they offered.

Otherwise, a useful tool can be found at [Raspberry Pi OS](https://www.raspberrypi.com/software/). Your RPI system should be any version of 64-bit Debian or Ubuntu. The desktop version of the system is NOT required. 

If you have any sensors, 

## Step 2: Get InfluxDB ready
Open your terminal,

 $ wget -q https://repos.influxdata.com/influxdata-archive_compat.key
 
 $ echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c influxdata-archive_compat.key' | sha256sum -c && cat influxdata-archive_compat.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null
 
 $ echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' | sudo tee /etc/apt/sources.list.d/influxdata.list
 
Please be advised that you should strictly follow these commands. Many other resources you may find on the Internet are equipped with out-of-date GPG keys which will cause installation problems.

After that, you can simply type

 $ Influx
 
To get into influx.

Create a new database 

>create database demo

>use demo

>create user grafana with password 'grafana' with all privileges

>grant all privileges on demo to grafana

>show users

to check if is added

# Step 3: Collect data from RPI and transfer data to cloud InfluxDB(1)
See file cloud.py

# Step 4； Get Google VM machine ready
to be added

# Step 5: Install InfluxDB(same as 2) and Install Grafana
See https://grafana.com/grafana/download

# Step 6: Run the previous .py file

$chmod +x /home/pi51/demo.py

$./demo.py

# Step 7: Step up Grafana Dashboard
See the json file

# Step 8: Results
<img width="962" alt="66" src="https://github.com/user-attachments/assets/5ab320f1-0c3a-45dc-9068-fcdfc412fc11">
