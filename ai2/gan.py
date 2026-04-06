import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.datasets as datasets
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt

# --- 1. Network Architectures ---
class Generator(nn.Module):
    def __init__(self, latent_dim, img_dim):
        super().__init__()
        self.gen = nn.Sequential(
            nn.Linear(latent_dim, 256),
            nn.LeakyReLU(0.2),
            nn.Linear(256, img_dim),
            nn.Tanh(),  # Output in range [-1, 1]
        )

    def forward(self, x):
        return self.gen(x)

class Discriminator(nn.Module):
    def __init__(self, img_dim):
        super().__init__()
        self.disc = nn.Sequential(
            nn.Linear(img_dim, 128),
            nn.LeakyReLU(0.2),
            nn.Linear(128, 1),
            nn.Sigmoid(),  # Output probability [0, 1]
        )

    def forward(self, x):
        return self.disc(x)

# --- 2. Hyperparameters & Setup ---
device = "cuda" if torch.cuda.is_available() else "cpu"
lr = 3e-4
z_dim = 64
image_dim = 28 * 28 * 1  # Flattened MNIST
batch_size = 32
epochs = 50

# Load MNIST Data
transform = transforms.Compose(
    [transforms.ToTensor(), transforms.Normalize((0.5,), (0.5,))]
)
dataset = datasets.MNIST(root="dataset/", transform=transform, download=True)
loader = DataLoader(dataset, batch_size=batch_size, shuffle=True)

# Initialize networks
disc = Discriminator(image_dim).to(device)
gen = Generator(z_dim, image_dim).to(device)

# Setup Optimizers and Loss
opt_disc = optim.Adam(disc.parameters(), lr=lr)
opt_gen = optim.Adam(gen.parameters(), lr=lr)
criterion = nn.BCELoss()

# --- 3. The Training Loop (The Missing Part) ---
print(f"Training on {device}...")

for epoch in range(epochs):
    for batch_idx, (real, _) in enumerate(loader):
        # 3a. Prepare Data
        real = real.view(-1, 784).to(device) # Flatten: [batch, 1, 28, 28] -> [batch, 784]
        batch_size = real.shape[0]

        ### Train Discriminator: maximize log(D(x)) + log(1 - D(G(z)))
        noise = torch.randn(batch_size, z_dim).to(device)
        fake = gen(noise)
        disc_real = disc(real).view(-1)
        lossD_real = criterion(disc_real, torch.ones_like(disc_real)) # Disc should say 1
        disc_fake = disc(fake).view(-1)
        lossD_fake = criterion(disc_fake, torch.zeros_like(disc_fake)) # Disc should say 0
        lossD = (lossD_real + lossD_fake) / 2
        
        disc.zero_grad()
        lossD.backward(retain_graph=True) # Retain graph because we reuse 'fake'
        opt_disc.step()

        ### Train Generator: maximize log(D(G(z))) or minimize log(1 - D(G(z)))
        output = disc(fake).view(-1)
        lossG = criterion(output, torch.ones_like(output)) # Gen wants Disc to say 1
        
        gen.zero_grad()
        lossG.backward()
        opt_gen.step()

    print(f"Epoch [{epoch+1}/{epochs}] Loss D: {lossD:.4f}, Loss G: {lossG:.4f}")

# --- 4. Generating and Visualizing the Image ---
print("\nGenerating final image...")
gen.eval() # Set generator to evaluation mode
with torch.no_grad():
    # Generate one final sample
    single_noise = torch.randn(1, z_dim).to(device)
    generated_image = gen(single_noise)
    
    # Reshape back to image format [1, 28, 28]
    generated_image = generated_image.view(1, 28, 28).cpu()
    
    # Un-normalize (from [-1, 1] back to [0, 1])
    generated_image = (generated_image + 1) / 2

plt.imshow(generated_image.squeeze(), cmap="gray")
plt.title("Generated MNIST Digit")
plt.axis("off")
plt.show()