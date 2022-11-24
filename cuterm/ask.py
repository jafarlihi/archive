import requests
import os
import pprint

if __name__ == '__main__':
    pp = pprint.PrettyPrinter(depth=4)
    headers = {'Authorization': os.environ['CLICKUP_API_KEY']}

    url = 'https://api.clickup.com/api/v2/team'
    resp = requests.get(url, headers=headers).json()
    team_id = resp['teams'][0]['id']

    url = 'https://api.clickup.com/api/v2/team/%s/space?archived=false' % team_id
    resp = requests.get(url, headers=headers).json()
    spaces = []

    for i in range(0, len(resp['spaces'])):
        spaces.append({
            'name': resp['spaces'][i]['name'],
            'id': resp['spaces'][i]['id'],
            'local_id': i
        })

    pp.pprint(spaces)

    space_local_id = input("Which space? (local_id): ")
    space = next(item for item in spaces if item['local_id'] == int(space_local_id))

    url = 'https://api.clickup.com/api/v2/space/%s/folder?archived=false' % space['id']
    resp = requests.get(url, headers=headers).json()
    folders = []

    for i in range(0, len(resp['folders'])):
        folders.append({
            'name': resp['folders'][i]['name'],
            'id': resp['folders'][i]['id'],
            'local_id': i
        })

    pp.pprint(folders)

    folder_local_id = input("Which folder? (local_id): ")
    folder = next(item for item in folders if item['local_id'] == int(folder_local_id))

    url = 'https://api.clickup.com/api/v2/folder/%s/list?archived=false' % folder['id']
    resp = requests.get(url, headers=headers).json()
    lists = []

    for i in range(0, len(resp['lists'])):
        lists.append({
            'name': resp['lists'][i]['name'],
            'id': resp['lists'][i]['id'],
            'local_id': i
        })

    pp.pprint(lists)

    list_local_id = input("Which list? (local_id): ")
    _list = next(item for item in lists if item['local_id'] == int(list_local_id))

    url = 'https://api.clickup.com/api/v2/list/%s/task?archived=false' % _list['id']
    resp = requests.get(url, headers=headers).json()
    tasks = []

    for i in range(0, len(resp['tasks'])):
        tasks.append({
            'name': resp['tasks'][i]['name'],
            'id': resp['tasks'][i]['id'],
            'description': resp['tasks'][i]['description'],
            'status': resp['tasks'][i]['status']['status'],
            'local_id': i
        })

    todo_tasks = [t for t in tasks if t['status'] in ['todo']]
    pp.pprint(todo_tasks)

