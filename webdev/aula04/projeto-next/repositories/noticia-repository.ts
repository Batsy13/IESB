import { NoticiaModel } from "@/model/noticia-model";

export interface NoticiaRepository {
    findAll(): Promise<NoticiaModel[]>;
}