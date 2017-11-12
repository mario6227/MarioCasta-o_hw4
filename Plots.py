import numpy as np
import scipy.io.wavfile
from matplotlib import cm
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation
import mpl_toolkits.mplot3d.axes3d as p3
from matplotlib.ticker import LinearLocator, FormatStrFormatter

#-----------------------------------------------------------------------------
#Grafica de la primera situacion y sonido
#-----------------------------------------------------------------------------

cuerda1 = np.genfromtxt('cuerda.txt', delimiter = '  ')
per = 2560
dt = 0.1*0.005/250.0
f = 1/dt

x = cuerda1[:,0]
T0 = cuerda1[:,1]
T8 = cuerda1[:,(per/8+1)]
T4 = cuerda1[:,(per/4+1)]
T2 = cuerda1[:,(per/2+1)]

medio = np.zeros(2560)

#Onda en el punto medio
for i in range(1,2560):
    medio[i] = cuerda1[64,i]

medio1s = np.tile(medio,1000)
    
plt.figure(1)
plt.plot(x,T0, label = 't = 0')
plt.plot(x,T8, label = 't = T/8')
plt.plot(x,T4, label = 't = T/4')
plt.plot(x,T2, label = 't = T/2')
plt.xlabel('Posicion [m]')
plt.ylabel('Amplitud')
plt.title('Cuerda con extremos fijos')
plt.legend(loc = 0);
plt.savefig('extremos_fijos.jpg')
plt.close()

#sonido
scipy.io.wavfile.write('sonido.wav', f, medio1s)

#-----------------------------------------------------------------------------
#Grafica de la segunda situacion y animacion
#-----------------------------------------------------------------------------

cuerda2 = np.genfromtxt('cuerda2.txt', delimiter = '  ')
per2 = 5120

x_2 = cuerda2[:,0]
T0_2 = cuerda2[:,1]
T8_2 = cuerda2[:,(per2/8+1)]
T4_2 = cuerda2[:,(per2/4+1)]
T2_2 = cuerda2[:,(per2/2+1)]

plt.figure(2)
plt.plot(x_2,T0_2, label = 't = 0')
plt.plot(x_2,T8_2, label = 't = T/8')
plt.plot(x_2,T4_2, label = 't = T/4')
plt.plot(x_2,T2_2, label = 't = T/2')
plt.xlabel('Posicion [m]')
plt.ylabel('Amplitud')
plt.title('Cuerda con perturbacion en un extremo')
plt.legend(loc = 0);
plt.savefig('extremos_perturbacion.jpg')
plt.close()

#Animacion
fig = plt.figure(3)
ax = plt.axes(xlim=(0, 0.64), ylim=(-5, 5))
line, = ax.plot([], [], lw=2)

def init():
    line.set_data([], [])
    return line,

def animate(i):
    x = cuerda2[:,0]
    y = cuerda2[:,(10*i+1)]
    line.set_data(x, y)
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=(per2/10), interval=20, blit=True)

#IMPORTANTE: requiere ffmepg
anim.save('cuerda.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

#-----------------------------------------------------------------------------
#Grafica de la tercera situacion (tambor) y animacion
#-----------------------------------------------------------------------------

tambor = np.genfromtxt('tambor.txt', delimiter = ' ')
#Se almacenan solo los valores cada T/16
tam0 = np.zeros((101,101))
tam8 = np.zeros((101,101))
tam4 = np.zeros((101,101))
tam2 = np.zeros((101,101))

for i in range(101):
    for j in range(101):
        tam0[i,j] = tambor[i, j]
        tam8[i,j] = tambor[101+i, j]
        tam4[i,j] = tambor[202+i, j]
        tam2[i,j] = tambor[303+i, j]

xtam = np.arange(0.0, 0.505, 0.5/100)
ytam = np.arange(0.0, 0.505, 0.5/100)
xtam, ytam = np.meshgrid(xtam, ytam)

fig = plt.figure(4)
ax = fig.gca(projection='3d')
surf = ax.plot_surface(xtam, ytam, tam0, cmap=cm.coolwarm, label = 't = 0')
ax.set_title('t = 0')
fig.colorbar(surf, shrink=0.5, aspect=5)
plt.savefig('tambor_t0.jpg')
plt.close()

fig = plt.figure(5)
ax = fig.gca(projection='3d')
surf = ax.plot_surface(xtam, ytam, tam8, cmap=cm.coolwarm, label = 't = T/8')
ax.set_title('t = T/8')
fig.colorbar(surf, shrink=0.5, aspect=5)
plt.savefig('tambor_t8.jpg')
plt.close()

fig = plt.figure(6)
ax = fig.gca(projection='3d')
surf = ax.plot_surface(xtam, ytam, tam4, cmap=cm.coolwarm, label = 't = T/4')
ax.set_title('t = T/4')
fig.colorbar(surf, shrink=0.5, aspect=5)
plt.savefig('tambor_t4.jpg')
plt.close()

fig = plt.figure(7)
ax = fig.gca(projection='3d')
surf = ax.plot_surface(xtam, ytam, tam2, cmap=cm.coolwarm, label = 't = T/2')
ax.set_title('t = T/2')
fig.colorbar(surf, shrink=0.5, aspect=5)
plt.savefig('tambor_t2.jpg')
plt.close()
