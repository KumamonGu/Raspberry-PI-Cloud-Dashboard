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

If you have any sensors, please set them up as the sensor provider required. **Please be advised that sensors must provide digital signal but not analog signal so that RPI GPIO can read such signals.** 

## Step 2: Get your Google VM machine ready
If you need a cloud VM dashboard, then this step is a must. Otherwise, please omit this step and go to Step 3.
### 1 Create a project on Google Cloud
You must have a Google Account to use Google Cloud. If you do not have one, you can sign up one at [Gmail](www.gmail.com)

Visit Google Developer-frames Console and log in with your account.

Click on Create Project. This will bring up the New Project dialog. Enter a name for the project and ensure that you have selected the correct Billing Account. An example screenshot is shown below:

![image](https://github.com/user-attachments/assets/eefffdfa-2389-488e-b103-cc79d2dfb796)

Click Create to begin the process of creating the project.

### 2 Create a virtual machine on Compute Engine
We need to create an instance on which we can run InfluxDB. This means we need to provision a VM (Linux-based) from the Compute Engine service. 

Follow these steps with details at https://cloud.google.com/compute/docs/quickstart-linux :

Click on Compute –> Compute Engine –> VM Instances.

Click on New Instance.

This will bring up a form for entering the details about your new instance. Pay attention to the following fields:

Give your instance a name. For example, influxdb-1

Select a zone closest to you. For example, us-central1-a. This doesn't really influence anything, though.

Select a machine type. I went with the lowest option e2.

Keep the boot disk image as the default one selected i.e. Debian

Leave all the other options at their default.

Click on the Create button.

Now you have your Vm, and you can connect to it remotely via the SSH button that google offered.

### 3 Change VM firewall policy
Set up a firewall rule to enable directly connecting to the Grafana GUI by external IP. 

In Google Cloud Dashboard, Follow these steps:

Click on Networking –> VPC network –> Firewall rules.

Click on Create Firewall Rule.

Pay attention to the following fields:

Set targets to all

Set your Source IP ranges as 0.0.0.0/0 to allow all packets unfiltered.

Specified Protocols and ports, tcp:8086; tcp:3000. Here 8086 is for influxdb and 3000 is for Grafana.

Leave all the other options at their default.

Click on the Create button.

## Step 3: Get InfluxDB ready
If you want to have a local dashboard, please do this step on your local Raspberry PI. Otherwise, Open your cloud VM,
In terminal, run these commands below:
```
 wget -q https://repos.influxdata.com/influxdata-archive_compat.key
 
 echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c influxdata-archive_compat.key' | sha256sum -c && cat influxdata-archive_compat.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null
 
 echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' | sudo tee /etc/apt/sources.list.d/influxdata.list
 ```
Please be advised that you should strictly follow these commands. Many other resources you may find on the Internet are equipped with out-of-date GPG keys which will cause installation problems.

After that, you can simply type
```
 Influx
 ```
To get into influx.
```
Create a new database 

>create database demo

>use demo

>create user grafana with password 'grafana' with all privileges

>grant all privileges on demo to grafana

>show users
```
to check if is added

## Step 4: Get Grafana Ready
If you want to have a local dashboard, please do this step on your local Raspberry PI. Otherwise, Open your cloud VM.

In the terminal, then run the commands from: https://grafana.com/grafana/download?platform=linux 
```
#Start Grafana by running:
$ sudo service grafana-server start
#This will start the grafana-server process as the grafana user, which was created during the package installation. 

#To configure the Grafana server to start at boot time:
$ sudo update-rc.d grafana-server defaults
#Then your grafana should be good to go.
```

## Step 5: Collect data from RPI and transfer data to cloud InfluxDB
Detailed code can be found within cloud.py. The current code contains:

1.Collect system data from local RPI

2.Simulated sensor data

3.Transfer these data to cloud side

Please be reivse this file accordingly to transfer your own datas to cloud.

## Step 6: Run the previous .py file
```
chmod +x /home/pi51/demo.py
./demo.py IP USER PASSWORD
```
IP is the external IP address of your cloud VM. USER is the username of the database, password is the authorization password.
# Step 7: Step up Grafana Dashboard
Use 
>HTTP://IP:3000
to log into grafana on cloud VM or RPI.

Choose Import dashboard, upload the .json file for accessing dashboard.

# Step 8: Results
Please see the final results of our dashboard.
<img width="962" alt="66" src="https://github.com/user-attachments/assets/5ab320f1-0c3a-45dc-9068-fcdfc412fc11">
