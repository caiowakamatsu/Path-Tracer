// This is meant as a demo program so I know what's going on and how to implement this on the gpu

let scene = new Scene(); // Create the CPU side scene, which has a lot more less "compressed" information

/* idk why I'm spending so much time on pseudo code, I guess I'm just hoping this helps me plan out the entire program */
let sphereSize = 3;
let size = 5;
let start = Math.floor(size / 2);
let end = size - start;
for(let x=start; x<end; x++) {
    for(let z=start; z<end; z++)
        scene.addShape(new Sphere(new Vector3(x * sphereSize + 1, 0, z * sphereSize + 1), Material.GLASS));
}

scene.setSky(new Texture("./assets/textures/sky1.jpg"));
