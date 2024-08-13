# Raspberry-PI-Cloud-Dashboard
A Raspberry PI Dashboard design on Cloud VM
Tools needed: InfluxDB, Grafana, Raspberry PI 5, Google Cloud VM

# Step 1: Set up Raspberry PI
You can set up your Raspberry PI to start. If your RPI comes with a pre-installed system(e.g. You bought it from companies like Canakit), please follow the instructions I've included here. Otherwise, a useful tool can be found at https://www.raspberrypi.com/software/.
Your RPI system should be Debian or Ubuntu. A Desktop version of the system is not needed.

# Step 2: Get InfluxDB ready
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
See file demo.py

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
