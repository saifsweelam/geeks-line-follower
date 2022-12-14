# import modules
import qrcode
from PIL import Image
 
# taking image which user wants
# in the QR code center
logo = Image.open('logo.jpg')
 
# taking base width
basewidth = 150
 
# adjust image size
wpercent = (basewidth/float(logo.size[0]))
hsize = int((float(logo.size[1])*float(wpercent)))
logo = logo.resize((basewidth, hsize), Image.ANTIALIAS)
qr_code = qrcode.QRCode(
    error_correction=qrcode.constants.ERROR_CORRECT_H
)
 
# taking url or text
url = 'https://github.com/saifsweelam/geeks-line-follower'
 
# adding URL or text to QRcode
qr_code.add_data(url)
 
# generating QR code
qr_code.make()
 
# adding color to QR code
qr_img = qr_code.make_image(
    fill_color="green", back_color="white").convert('RGB')
 
# set size of QR code
pos = ((qr_img.size[0] - logo.size[0]) // 2,
       (qr_img.size[1] - logo.size[1]) // 2)
qr_img.paste(logo, pos)
 
# save the QR code generated
qr_img.save('projectQR.png')

print('QR code generated!')