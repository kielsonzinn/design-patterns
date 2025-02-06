#include <iostream>

class Pagamento {

public:
    int id;

    explicit Pagamento( int id ) :
        id( id ) {}

};

class ProcessaPagamento {

public:
    void processar( Pagamento* pagamento ) const {

        processarRecebimento( pagamento );
        processarDesconto( pagamento );
        processarAcrescimo( pagamento );
        gravar( pagamento );

    }

    virtual void processarRecebimento( Pagamento* pagamento ) const = 0;

    virtual void processarDesconto( Pagamento* pagamento ) const {
        std::cout << "Aplicando desconto no pagamento " << pagamento->id << std::endl;
    }

    virtual void processarAcrescimo( Pagamento* pagamento ) const {
        std::cout << "Aplicando acréscimo no pagamento " << pagamento->id << std::endl;
    }

    virtual void gravar( const Pagamento* pagamento ) const {
        std::cout << "Gravando pagamento " << pagamento->id << std::endl;
    }

};

class ProcessaPagamentoCartao : public ProcessaPagamento {

public:
    void processarRecebimento( Pagamento* pagamento ) const override {
        std::cout << "Processando pagamento " << pagamento->id << " via Cartão." << std::endl;
    }

};

class ProcessaPagamentoCartaoPresente : public ProcessaPagamento {

public:
    void processarRecebimento( Pagamento* pagamento ) const override {
        std::cout << "Processando pagamento " << pagamento->id << " via Cartão Presente.\n";
    }

    void processarDesconto( Pagamento* pagamento ) const override {
        std::cout << "Desconto não pode ser aplicado ao pagamento " << pagamento->id << " via Cartão Presente." << std::endl;
    }

    void processarAcrescimo( Pagamento* pagamento ) const override {
        std::cout << "Acréscimo não pode ser aplicado ao pagamento " << pagamento->id << " via Cartão Presente." << std::endl;
    }

};

class ProcessaPagamentoCheque : public ProcessaPagamento {

public:
    void processarRecebimento( Pagamento* pagamento ) const override {
        std::cout << "Processando pagamento " << pagamento->id << " via Cheque." << std::endl;
    }

    void gravar( const Pagamento* pagamento ) const override {
        ProcessaPagamento::gravar( pagamento );
        std::cout << "Gravando pagamento " << pagamento->id << " na tabela de Cheques." << std::endl;
    }

};

int main() {

    Pagamento pagamento1( 1 ), pagamento2( 2 ), pagamento3( 3 );

    ProcessaPagamentoCartao cartao;
    ProcessaPagamentoCheque cheque;
    ProcessaPagamentoCartaoPresente cartaoPresente;

    cartao.processar( &pagamento1 );
    cheque.processar( &pagamento2 );
    cartaoPresente.processar( &pagamento3 );

    return 0;

}
