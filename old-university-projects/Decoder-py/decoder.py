import os, sys, time, hashlib, random
import MySQLdb
from daemon import runner
from ConfigParser import SafeConfigParser

def consists_of_allowed_characters(text, allowed_characters):
    for character_number in range(0, len(text)):
        if text[character_number] not in allowed_characters:
            return False
    return True

def compile_mcrts():
    if not os.path.exists('/root/decoder-app/Merchants/'):
        os.makedirs('/root/decoder-app/Merchants/')
    if not os.path.exists('/root/decoder-app/Cache/'):
        os.makedirs('/root/decoder-app/Cache/')
    if not os.path.exists('/root/decoder-app/LOGS/'):
        os.makedirs('/root/decoder-app//LOGS/')

    import glob
    file_list = glob.glob("/root/decoder-app/Merchants/MCRT_*")

    from time import strftime

    option_list = ['SYMBOL', 'DLTM', 'LENGTH', 'RPT', 'TLEN', 'PLEN']
    dtmf_characters = ['*', '#', 'A', 'B', 'C', 'D', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    error_list = []
    comment_starter = '//'

    for c in range(0, len(file_list)):
        file = open(file_list[c], 'r')
        file_contents = file.readlines()
        for c2 in range(0, len(file_contents)):
            file_contents[c2] = file_contents[c2].split(comment_starter, 1)[0]
            file_contents[c2] = file_contents[c2].split('\n', 1)[0]
            file_contents[c2] = file_contents[c2].replace(' ', '')
        file_contents = filter(None, file_contents)
        file_contents_str = ' '.join(file_contents)

        for option in option_list:
            if not any(option + '=' in x for x in file_contents):
                error_list.append([file_list[c], 2, strftime("%Y/%m/%d-%H:%M:%S"), option])

            if file_contents_str.count(option) > 1:
                error_list.append([file_list[c], 4, strftime("%Y/%m/%d-%H:%M:%S"), option])

        for element in file_contents:
            if (option_list[0] + '=' not in element) \
                    and (option_list[1] + '=' not in element) \
                    and (option_list[2] + '=' not in element) \
                    and (option_list[3] + '=' not in element) \
                    and (option_list[4] + '=' not in element) \
                    and (option_list[5] + '=' not in element):
                error_list.append([file_list[c], 5, strftime("%Y/%m/%d-%H:%M:%S"), element])

            if 'SYMBOL=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'SYMBOL'])
                elif not consists_of_allowed_characters(element.rsplit('=', 1)[1], dtmf_characters):
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'SYMBOL'])

            if 'DLTM=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'DLTM'])
                elif not consists_of_allowed_characters(element.rsplit('=', 1)[1], dtmf_characters):
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'DLTM'])

            if 'LENGTH=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'LENGTH'])
                elif not element.rsplit('=', 1)[1].isdigit():
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'LENGTH'])

            if 'RPT=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'RPT'])
                elif not element.rsplit('=', 1)[1].isdigit():
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'RPT'])

            if 'TLEN=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'TLEN'])
                elif not element.rsplit('=', 1)[1].isdigit():
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'TLEN'])

            if 'PLEN=' in element:
                if len(element.rsplit('=', 1)[1]) == 0:
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'PLEN'])
                elif not element.rsplit('=', 1)[1].isdigit():
                    error_list.append([file_list[c], 3, strftime("%Y/%m/%d-%H:%M:%S"), 'PLEN'])

    files_to_compile = list(file_list)
    for error in error_list:
        for file in file_list:
            if (error[0] == file) and (file in files_to_compile):
                files_to_compile.remove(file)

    message_list = ['[%s] Configuration of merchant type "%s" loaded.\n\n',
                    '[%s] Configuration of merchant type "%s" skipped, not loaded.\n',
                    '[%s] Option "%s" not found.\n',
                    '[%s] Parameter for option "%s" is incorrect.\n',
                    '[%s] Option "%s" duplicated.\n',
                    '[%s] String "%s" is not supported.\n']
    mr_logs = open("./LOGS/Merchant_types.log", "a")

    for file in files_to_compile:
        filename = file.split('/', 2)[-1]
        mr_logs.write(message_list[0] % (strftime("%Y/%m/%d-%H:%M:%S"), filename))

    for file in file_list:
        if file not in files_to_compile:
            filename = file.split('/', 2)[-1]
            mr_logs.write(message_list[1] % (strftime("%Y/%m/%d-%H:%M:%S"), filename))
            for error in error_list:
                if error[0] == file:
                    mr_logs.write(message_list[error[1]] % (error[2], error[3]))
            mr_logs.write('\n')

    sanitized_mcrts = []

    for c in range(0, len(files_to_compile)):
        with open(files_to_compile[c], 'r') as mcrt:
            mcrt_lines = mcrt.readlines()
            for c2 in range(0, len(mcrt_lines)):
                if mcrt_lines[c2].find(comment_starter) != 1:
                    mcrt_lines[c2] = mcrt_lines[c2].split(comment_starter, 1)[0]
                    mcrt_lines[c2] = mcrt_lines[c2].split('\n', 1)[0]
                    mcrt_lines[c2] = mcrt_lines[c2].replace(' ', '')
            mcrt_lines = filter(None, mcrt_lines)
            sanitized_mcrts.append(mcrt_lines)

    mcrt_compile = open("/root/decoder-app/Cache/mcrt_compiled", "w")

    for c in range(0, len(sanitized_mcrts)):
        mcrt_compile.write('[mcrt #' + str(c) + ']\n')
        for c2 in range(0, len(sanitized_mcrts[c])):
            mcrt_compile.write(sanitized_mcrts[c][c2] + '\n')

def load_templates():
    mcrts = SafeConfigParser()
    mcrts.read('/root/decoder-app/Cache/mcrt_compiled')

    templates = []

    for section in mcrts.sections():
        template_delimiter = mcrts.get(section, 'DLTM')
        length = mcrts.get(section, 'LENGTH')
        allowed_characters = mcrts.get(section, 'SYMBOL')

        templates.append([template_delimiter, length, allowed_characters])
    return templates

def decode(raw_transmission):
    templates = load_templates()

    for template in templates:
        parts = raw_transmission.split(template[0])

        for part in parts:
            if len(part) == int(template[1]):
                if consists_of_allowed_characters(part, template[2]):
                    return part

def md5(filename):
    hash_md5 = hashlib.md5()
    with open(filename, "rb") as f:
        for chunk in iter(lambda: f.read(256), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def store(TID, file_content, decoded_string, DateTime):
    config = SafeConfigParser()
    config.read('/root/decoder-app/config')
    database_settings = dict(config.items('Database'))

    connection = MySQLdb.connect(host=database_settings['host'], port=int(database_settings['port']), user=database_settings['username'], passwd=database_settings['password'], db=database_settings['database'])
    db = connection.cursor()

    db.execute("INSERT INTO " + database_settings['table'] + " (TID, Raw_Transmission, Decoded_Transmission, DateTime)" + " VALUES ('" + str(TID) + "','" + file_content + "','" + decoded_string + "','" + str(DateTime) + "')")

    connection.commit()
    connection.close()

class DecoderApp():
    def __init__(self):
        self.stdin_path = '/dev/null'
        self.stdout_path = '/dev/tty'
        self.stderr_path = '/dev/tty'
        self.pidfile_path =  '/tmp/decoder-app.pid'
        self.pidfile_timeout = 5

    def run(self):
        if not os.path.exists('/root/decoder-app/Merchants/'):
            os.makedirs('/root/decoder-app/Merchants/')
        if not os.path.exists('/root/decoder-app/Cache/'):
            os.makedirs('/root/decoder-app/Cache/')
        if not os.path.exists('/root/decoder-app/LOGS/'):
            os.makedirs('/root/decoder-app/LOGS/')

        first_hash = md5('/var/records/test.txt')
        last_hash = first_hash

        while True:
            time.sleep(0.001)
            if md5('/var/records/test.txt') != last_hash:
                last_hash = md5('/var/records/test.txt')
                with open('/var/records/test.txt', 'r') as file:
                    file_content = str(file.read())
                    decoded_string = str(decode(file_content))
                    TID = str(random.randrange(1000000000,9999999999)) + str(time.time()).replace(".", "")
                    DateTime = str(time.time()).replace(".", "")

                store(TID, file_content, decoded_string, DateTime)

if sys.argv[1] == 'mr':
    compile_mcrts()
    print "Merchant files were reloaded. Please check /root/decoder-app/LOGS/Merchant_types.log file for operations logs."

app = DecoderApp()
daemon_runner = runner.DaemonRunner(app)
daemon_runner.do_action()
