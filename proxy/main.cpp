#include <iostream>
#include <map>
#include <list>
#include <memory>
#include <random>

class Produto {

public:
    std::string codigo;
    std::string nome;
    double preco;

    Produto( const std::string& codigo, const std::string& nome, const double preco ) :
        codigo( codigo ),
        nome( nome ),
        preco( preco ) {}
};

class ProdutoRepository {

public:
    virtual Produto* buscarProduto( const std::string& codigo ) = 0;

    virtual ~ProdutoRepository() = default;

};

class ProdutoDatabase : public ProdutoRepository {

public:
    Produto* buscarProduto( const std::string& codigo ) override {
        static std::random_device rd;
        static std::mt19937 gen( rd() );
        static std::uniform_real_distribution<double> dist( 10.0, 500.0 );

        return new Produto( codigo, "Produto " + codigo, dist( gen ) );
    }
};

class ProdutoProxy : public ProdutoRepository {

private:
    ProdutoDatabase _produtoDatabase;
    std::map<std::string, Produto*> _produtoByCodigo;
    size_t _cacheLimit;

public:
    ProdutoProxy( size_t cacheLimit = 10 ) :
        _cacheLimit( cacheLimit ) {}

    Produto* buscarProduto( const std::string& codigo ) override {
        auto it = _produtoByCodigo.find( codigo );

        if ( it != _produtoByCodigo.end() ) {
            std::cout << "[ CACHE ] Produto encontrado no cache" << std::endl;
            return new Produto( *it->second );
        }

        std::cout << "[    DB ] Consultando no banco de dados" << std::endl;
        Produto* produto = _produtoDatabase.buscarProduto( codigo );
        addToCache( codigo, produto );

        return new Produto( *produto );
    }

private:
    void addToCache( const std::string& codigo, Produto* produto ) {

        if ( _produtoByCodigo.size() >= _cacheLimit ) {
            _produtoByCodigo.erase( codigo );
        }

        _produtoByCodigo[codigo] = produto;

    }

};

void vender( ProdutoRepository& repo, const std::string& codigo ) {
    std::unique_ptr<Produto> produto( repo.buscarProduto( codigo ) );
    std::cout << "[    UI ] Venda realizada" << std::endl;
}

int main() {
    ProdutoProxy proxy( 10 );

    vender( proxy, "001" );
    vender( proxy, "002" );
    vender( proxy, "001" );
    vender( proxy, "003" );
    vender( proxy, "004" );
    vender( proxy, "005" );
    vender( proxy, "006" );
    vender( proxy, "007" );
    vender( proxy, "008" );
    vender( proxy, "009" );
    vender( proxy, "010" );
    vender( proxy, "011" );
    vender( proxy, "001" );

    return 0;

}
