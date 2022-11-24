import requests
import os
import pprint

if __name__ == '__main__':
    pp = pprint.PrettyPrinter(depth=4)
    headers = {'Authorization': os.environ['CLICKUP_API_KEY']}

    url = 'https://api.clickup.com/api/v2/list/%s/task?archived=false' % os.environ['CLICKUP_LIST_ID']
    resp = requests.get(url, headers=headers).json()
    tasks = []

    for i in range(0, len(resp['tasks'])):
        tasks.append({
            'name': resp['tasks'][i]['name'],
            'description': resp['tasks'][i]['description'],
            'status': resp['tasks'][i]['status']['status'],
        })

    todo_tasks = [t for t in tasks if t['status'] in ['todo']]
    pp.pprint(todo_tasks)

