#include <iostream>
#include <vector>
#include <memory>

class Cliente {
public:
    int id;
    explicit Cliente( int id ) :
        id( id ) {}
};

class Usuario {
public:
    int id;
    explicit Usuario( int id ) :
        id( id ) {}
};

class Item {
public:
    double preco;
    double quantidade;
    explicit Item( const double preco, const double quantidade ) :
        preco( preco ),
        quantidade( quantidade ) {}
};

class Recebimento {
public:
    double valor;
    explicit Recebimento( double valor ) :
        valor( valor ) {}
};

class Venda {

public:
    Venda() :
        nrVenda( 0 ) {}

    int nrVenda;
    std::unique_ptr<Cliente> cliente;
    std::unique_ptr<Usuario> usuario;
    std::vector<Item*> itens;
    std::vector<Recebimento*> recebimentos;

};

class VendaBuilder {
private:
    std::unique_ptr<Venda> venda;

public:
    VendaBuilder() :
        venda( new Venda() ) {}

    VendaBuilder* withNrVenda( int nrVenda ) {
        venda->nrVenda = nrVenda;
        return this;
    }

    VendaBuilder* withCliente( int clienteId ) {
        venda->cliente.reset( new Cliente( clienteId ) );
        return this;
    }

    VendaBuilder* withUsuario( int usuarioId ) {
        venda->usuario.reset( new Usuario( usuarioId ) );
        return this;
    }

    VendaBuilder* withItens( const std::vector<Item*>& itens ) {
        venda->itens = itens;
        return this;
    }

    VendaBuilder* withRecebimentos( const std::vector<Recebimento*>& recebimentos ) {
        venda->recebimentos = recebimentos;
        return this;
    }

    std::unique_ptr<Venda> build() {
        return std::move( venda );
    }
};

int main() {
    Item item1( 1, 5.00 ), item2( 3, 10.00 );
    Recebimento receb1( 7.5 ), receb2( 7.5 );

    std::unique_ptr<Venda> venda = VendaBuilder()
                                   .withNrVenda( 12345 )
                                   ->withCliente( 1 )
                                   ->withUsuario( 101 )
                                   ->withItens( { &item1, &item2 } )
                                   ->withRecebimentos( { &receb1, &receb2 } )
                                   ->build();

    return 0;
}
