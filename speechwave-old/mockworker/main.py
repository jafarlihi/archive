import os
import time
import subprocess
import logging

logging.basicConfig(filename='worker.log', filemode='a', format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO)
languages = ['Afrikaans', 'Albanian', 'Amharic', 'Arabic', 'Armenian', 'Assamese', 'Azerbaijani', 'Bashkir', 'Basque', 'Belarusian', 'Bengali', 'Bosnian', 'Breton', 'Bulgarian', 'Burmese', 'Castilian', 'Catalan', 'Chinese', 'Croatian', 'Czech', 'Danish', 'Dutch', 'English', 'Estonian', 'Faroese', 'Finnish', 'Flemish', 'French', 'Galician', 'Georgian', 'German', 'Greek', 'Gujarati', 'Haitian', 'Haitian Creole', 'Hausa', 'Hawaiian', 'Hebrew', 'Hindi', 'Hungarian', 'Icelandic', 'Indonesian', 'Italian', 'Japanese', 'Javanese', 'Kannada', 'Kazakh', 'Khmer', 'Korean', 'Lao', 'Latin', 'Latvian', 'Letzeburgesch', 'Lingala', 'Lithuanian', 'Luxembourgish', 'Macedonian', 'Malagasy', 'Malay', 'Malayalam', 'Maltese', 'Maori', 'Marathi', 'Moldavian', 'Moldovan', 'Mongolian', 'Myanmar', 'Nepali', 'Norwegian', 'Nynorsk', 'Occitan', 'Panjabi', 'Pashto', 'Persian', 'Polish', 'Portuguese', 'Punjabi', 'Pushto', 'Romanian', 'Russian', 'Sanskrit', 'Serbian', 'Shona', 'Sindhi', 'Sinhala', 'Sinhalese', 'Slovak', 'Slovenian', 'Somali', 'Spanish', 'Sundanese', 'Swahili', 'Swedish', 'Tagalog', 'Tajik', 'Tamil', 'Tatar', 'Telugu', 'Thai', 'Tibetan', 'Turkish', 'Turkmen', 'Ukrainian', 'Urdu', 'Uzbek', 'Valencian', 'Vietnamese', 'Welsh', 'Yiddish', 'Yoruba']


def is_tool(name):
    from shutil import which
    return which(name) is not None


def main():
    #if not is_tool('whisper'):
    #    print('Whisper not found, exiting')
    #    exit(1)

    while True:
        time.sleep(5)
        input = os.listdir('/home/user/input-bucket')
        output = os.listdir('/home/user/output-bucket')
        output = list(map((lambda i: os.path.splitext(i)[0]), output))
        not_in_output = []
        for i in input:
            if i not in output:
                not_in_output.append(i)
        if len(not_in_output):
            logging.debug('Found unprocessed files: ' + ' '.join(not_in_output))
        if len(not_in_output):
            logging.info('Processing: ' + not_in_output[0])
            f = open('/home/user/output-bucket/' + not_in_output[0] + '.lock', 'a')
            f.write('locked')
            f.close()
            language = None
            for l in languages:
                if l in not_in_output[0]:
                    language = l
            if 'translate' in not_in_output[0]:
                if language:
                    #process = subprocess.Popen('whisper --model large --language ' + language + ' --task translate -o /home/user/output-bucket/ /home/user/input-bucket/' + not_in_output[0], shell=True, stdout=subprocess.PIPE)
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.txt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.srt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.vtt', shell=True)
                    process.wait()
                else:
                    #process = subprocess.Popen('whisper --model large --task translate -o /home/user/output-bucket/ /home/user/input-bucket/' + not_in_output[0], shell=True, stdout=subprocess.PIPE)
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.txt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.srt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.vtt', shell=True)
                    process.wait()
            else:
                if language:
                    #process = subprocess.Popen('whisper --model large --language ' + language + ' -o /home/user/output-bucket/ /home/user/input-bucket/' + not_in_output[0], shell=True, stdout=subprocess.PIPE)

                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.txt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.srt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.vtt', shell=True)
                    process.wait()
                else:
                    #process = subprocess.Popen('whisper --model large -o /home/user/output-bucket/ /home/user/input-bucket/' + not_in_output[0], shell=True, stdout=subprocess.PIPE)
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.txt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.srt', shell=True)
                    process.wait()
                    process = subprocess.Popen('touch /home/user/output-bucket/' + not_in_output[0] + '.vtt', shell=True)
                    process.wait()
            #process.wait()
            os.remove('/home/user/input-bucket/' + not_in_output[0])
            logging.info('Processed: ' + not_in_output[0]);


if __name__ == '__main__':
    main()
