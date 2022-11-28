import time

a = 27
b = 17


tnow = time.time()
tpre = time.time()

wnow = 0
wpre = 0
u = 24 #v

while True:
	
	tnow = time.time()
	Ts =(tnow - tpre)
	wnow = (1-(a*Ts))*wpre + b*Ts*u


	print(wnow , Ts)

	#update
	wpre = wnow
	tpre = tnow

	time.sleep(0.03)