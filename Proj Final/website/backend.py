from itertools import count
import json
import flask
import requests

app = flask.Flask(__name__, static_url_path='/static')
 
ae="Project_Data"
cnt="Node1"
cnt2="Node2"
cnt3="Node3"
uriCse="http://127.0.0.1:8080/~/in-cse/in-name"

uriAe=uriCse+'/'+ae
uriCnt=uriAe+'/'+cnt
uri=uriCnt+"/la"

uriCnt2=uriAe+'/'+cnt2
uri2=uriCnt2+"/la"

uriCnt3=uriAe+'/'+cnt3
uri3=uriCnt3+"/la"

spacing = 5
print("Hello")
loginpw = "admin"

headers = { 'X-M2M-Origin': 'admin:admin', 'Content-type': 'application/json' } 

# { dist1 , dist2 , vel , status , risk}

# getdata=requests.get(uri,headers=headers)
# print(getdata)
# string = getdata.json()
# print(string)

# getdata=requests.get(uri,headers=headers)
# string = getdata.json()
# newdata= json.loads(string['m2m:cin']['con']) 
# print(newdata)

@app.route('/data',methods=["GET"])
def mainpage():
    if(flask.request.method=="GET"):
        getdata=requests.get(uri3,headers=headers)
        string = getdata.json()
        print(string)
        # string = string.replace("'",'"')
        newdata= json.loads(string['m2m:cin']['con'])
        print(newdata)
        # d1 = newdata['dist1']
        # d2 = newdata['dist2']
        # angle=0
        # absangle=0
        # dist=min(d1,d2)     
        # vel = newdata['vel']
        # risk = newdata['risk']
        # riskangle = 10
        return flask.render_template('index.html',count = newdata)

# @app.route('/',methods=["POST","GET"])
# def login():
#     if(flask.request.method == "POST"):
#         print("Entered Login")
#         Password = flask.request.form['name']
#         print("Got a Login Request Password: ",Password)
#         if(Password==loginpw):
#             return flask.redirect(flask.url_for('mainpage'))
#         else:
#             return flask.render_template('invalid.html')
#     else:
#         return flask.render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)