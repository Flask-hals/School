#! /usr/bin/env python3
from flask import Flask, render_template, request
from data import *
#from data import db

app = Flask(__name__)

def read_data():
    db = load("/home/jakno825/Presentationslager/datalager.json")
    return db
db = read_data()

@app.route('/')
def home():
    latest_project = search(db, "end_date")
    return render_template('index.html', latest_project=latest_project)

@app.route('/list', methods=["GET"])
def list():
    sort_by = request.args.get('sort_by') or 'start_date'
    sort_order = request.args.get('sort_order')
    search_func = request.args.get('search_func') or None
    search_fields = request.args.getlist('search_fields')
    if search_fields == ['']:
        search_fields = None
    projects = search(db, sort_by=sort_by, sort_order=sort_order, search_fields=search_fields, search=search_func)

    return render_template('list.html', projects=projects)

@app.route('/techniques', methods=["GET"])
def techniques():
    selected_techniques = request.args.getlist('selected_techniques')
    techniques = get_techniques(db)
    projects = search(db, techniques=selected_techniques)
    return render_template('techniques.html', techniques=techniques, projects=projects)

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/project')
def project():
    project_id = 
    latest_project = search(db, "end_date")
    return render_template('project.html', latest_project=latest_project)

if __name__ == '__main__':
    app.run(debug=True)
