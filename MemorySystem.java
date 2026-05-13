import java.util.ArrayList;

/* Ehab Elsaigh
 * MMU First-Fit
 */

class Block {
    int pid;
    int size;
    boolean free;

    public Block(int size) {
        this.pid = 0;
        this.size = size;
        this.free = true;
    }

    public String toString() {
        return free ? "[F:" + size + "]" : "[P" + pid + ":" + size + "]";
    }
}

class MMU {
    ArrayList<Block> mem = new ArrayList<>();

    public MMU(int size) {
        mem.add(new Block(size));
    }

    public boolean alloc(int pid, int req) {
        for (int i = 0; i < mem.size(); i++) {
            Block b = mem.get(i);
            if (b.free && b.size >= req) {
                if (b.size > req) {
                    Block left = new Block(b.size - req);
                    b.size = req;
                    mem.add(i + 1, left);
                }
                b.free = false;
                b.pid = pid;
                return true;
            }
        }
        return false;
    }

    public void free(int pid) {
        for (Block b : mem) {
            if (b.pid == pid && !b.free) {
                b.free = true;
                b.pid = 0;
            }
        }
        compact();
    }

    private void compact() {
        for (int i = 0; i < mem.size() - 1; i++) {
            Block curr = mem.get(i);
            Block next = mem.get(i + 1);
            if (curr.free && next.free) {
                curr.size += next.size;
                mem.remove(i + 1);
                i--; // check again
            }
        }
    }

    public void print() {
        for (Block b : mem) System.out.print(b + " ");
        System.out.println();
    }
}

public class MemorySystem {
    public static void main(String[] args) {
        MMU mmu = new MMU(1024);
        
        mmu.alloc(1, 200);
        mmu.alloc(2, 300);
        mmu.alloc(3, 150);
        mmu.print();

        mmu.free(2);
        mmu.print();

        mmu.alloc(4, 250);
        mmu.print();

        mmu.free(1);
        mmu.free(3);
        mmu.free(4);
        mmu.print();
    }
}