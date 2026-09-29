```d
Table machines {

id bigint [pk, increment]

name varchar(100) [not null]

model varchar(100) [not null]

location varchar(100) [not null]

status varchar(20) [not null, default: 'ACTIVE']

}

  

Table sensors {

id bigint [pk, increment]

machine_id bigint [not null]

name varchar(100) [not null]

sensor_type varchar(50) [not null]

unit varchar(20) [not null]

}

  

Table measurements {

id bigint [pk, increment]

sensor_id bigint [not null]

value float [not null]

timestamp timestamp [not null]

}

  

Table alerts {

id bigint [pk, increment]

machine_id bigint [not null]

sensor_id bigint [not null]

value float [not null]

threshold float [not null]

severity varchar(10) [not null]

resolved boolean [not null, default: false]

created_at timestamp [not null]

}

  

Table maintenance {

id bigint [pk, increment]

machine_id bigint [not null]

technician_id bigint

maintenance_type varchar(20) [not null]

description text [not null]

scheduled_date date [not null]

completed boolean [not null, default: false]

completed_date date

}

  

Table auth_user {

id bigint [pk, increment]

username varchar(150) [not null]

email varchar(254)

}

  

Ref: sensors.machine_id > machines.id

  

Ref: measurements.sensor_id > sensors.id

  

Ref: alerts.machine_id > machines.id

  

Ref: alerts.sensor_id > sensors.id

  

Ref: maintenance.machine_id > machines.id

  

Ref: maintenance.technician_id > auth_user.id
```