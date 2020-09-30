####################################
# AM205 Workshop on Randomized
# Linear Algebra | September 2020
# Y. Luna Lin
####################################

import numpy as np
import numpy.random as random
import matplotlib.pyplot as plt
import time

if __name__ == "__main__":

    r = 100
    fig, axs = plt.subplots(1, 3, sharey='all', figsize=(40, 10))

    # Load the image and perform regular SVD decompositionn
    eagle = plt.imread("eagle.jpg")
    eagle = np.mean(eagle, axis=2)
    axs[0].set_title("Original Image")
    axs[0].axis('off')
    axs[0].imshow( eagle , cmap="gray")

    ############# Regular SVD #############
    reg_t = time.time()
    U, S, V = np.linalg.svd(eagle, full_matrices=0)
    reg_t = time.time() - reg_t

    # Reconstructing the image
    axs[1].set_title('Reconstructed, SVD r={}, time={:4.2f} s'.format(r, reg_t))
    axs[1].axis('off')
    axs[1].imshow( np.matmul( np.dot(U[:, :r], np.diag(S[:r])), V[:r, :]), cmap="gray")

    ############# Randomized SVD #############
    red_t = time.time()

    # Sample using a Gaussian random matrix
    redEagle = np.matmul(eagle, random.randn(eagle.shape[1], r) )

    # QR factorization of the sampled matrix
    Q, R = np.linalg.qr(redEagle, mode='reduced')

    # Project the original matrix into the orthogonal matrix Q
    redEagleProj = np.matmul(Q.transpose(), eagle)

    # Perform SVD on the projected, reduced matrix
    Up, Sp, Vp = np.linalg.svd(redEagleProj, full_matrices=0)

    # Project the left singular vectors back into original space
    Ur = np.matmul(Q, Up)

    red_t = time.time() - red_t

    # Reconstructing the image
    axs[2].set_title('Reconstructed, Randomized SVD r={}, time={:4.2f} s'.format(r, red_t))
    axs[2].axis('off')
    axs[2].imshow( np.matmul( np.dot(Ur[:, :r], np.diag(Sp[:r])), Vp[:r, :]), cmap="gray")
    plt.show()
