import { NoticiaModel } from "@/model/noticia-model";
import { NoticiaRepository } from "./noticia-repository";
import { readFile } from "fs/promises";
import { resolve } from "path";

const ROOT_DIR = process.cwd();
const DATA_DIR = resolve(ROOT_DIR, "db", "seed", "noticias.json");

export class JsonNoticiaRepository implements NoticiaRepository {
    async findAll(): Promise<NoticiaModel[]> {
        const json_content = await readFile(DATA_DIR, 'utf-8');
        const noticias_array = JSON.parse(json_content.toString());
        const { noticias } = noticias_array;
        
        return noticias;
    }
}

export const jsonNoticiaRepository = new JsonNoticiaRepository();