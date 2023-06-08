from oneM2M_functions import *
# uri_cse = "http://192.168.104.84:8080/~/in-cse/in-name"
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
# http://192.168.104.84:8080/
ae = "Project_Data"
create_ae(uri_cse, ae)
cnt = "Node1"
cnt2= "Node2"
cnt3 = "Node3"

uri_ae = uri_cse + "/" + ae
create_cnt(uri_ae, cnt)
create_cnt(uri_ae,cnt2)
create_cnt(uri_ae,cnt3)
uri_cnt = uri_ae + "/" + cnt
uri_cnt2 = uri_ae + "/" + cnt2
uri_cnt3 = uri_ae + "/" + cnt3
create_data_cin(uri_cnt, "you_are_done")    
create_data_cin(uri_cnt2, "you_are_done")  
create_data_cin(uri_cnt3, "you_are_done")