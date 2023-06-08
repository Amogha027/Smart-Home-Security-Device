from oneM2M_functions import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

ae = "Project_Data"
create_ae(uri_cse, ae)
cnt = "Node1"

uri_ae = uri_cse + "/" + ae
create_cnt(uri_ae, cnt)

uri_cnt = uri_ae + "/" + cnt
create_data_cin(uri_cnt, "you_are_done")