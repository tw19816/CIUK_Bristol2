import smtplib
import email.message
import sys
import os


def send_email(subject, msg):
    try:
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.ehlo()
        server.starttls()
        server.ehlo()
        ID = 'ciukbris@gmail.com'
        PASSWORD = sys.argv[3]
        email_reciever = 'nc19723@bristol.ac.uk'
        server.login(ID, PASSWORD)
        message = 'Subject:{} \n\n {}'.format(subject, msg)
        server.sendmail(ID, email_reciever, message)

    finally:
        server.quit()

dirname = sys.argv[1]
dirList = [dirname + "/" +name for name in os.listdir(dirname)]
fulltxt = ""
for filename in dirList:
    with open(filename, "r") as f:
        text = f.read()
    fulltxt += filename + "\n" + text + "\n\n"
msg = email.message.Message()
msg.add_header('Content-Type', 'text/plain')
msg.set_payload(fulltxt)

subject = "Report "+ sys.argv[2]

send_email(subject, msg)
